# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

# 基本方針
- 回答は日本語で対応も日本語で
- planモードの時は、まず plan、その後 implementation
- 変更ファイル一覧を最後に書く
- コード出力は UTF-8 で行ってください。

# 経緯
- このディレクトリは私の友達が、「ずんだもんが車を運転するゲーム」を作りたいといい始めてスタートしました。
- 友達は車についての知識はありますが、ゲームについての知識がないため、車の機能関数については頭の中や実際のコードで形になっているところも多いらしいですが、見た目としての何ができているか、どのように動くかが自分でもわかってないらしいです。
- 思い描いているゲームは、画面にアクセルやブレーキなど基本のUIと機能、そしてクラッチやウインカー、サイドブレーキなど車の細かい操作を実際に 動かせるようなマニアックなゲームを作りたがっています。
- 友達からもらった現状の中途半端ともいえるコードがあります。
- ひとまずこれらのファイルを読み解いてほしいです。
- その話を聞いて、私に手伝えることがないか模索しています。

# CLAUDEでの実装の中での最初のお願い
- 回答が完了したら音を鳴らす機能が欲しいです。
  - 実装が完了したら音声かWindowsの通知機能を使ってわかるようにしてください。
-  コンテキストウィンドウの使用率が高くなってきたら警告をしてください。
-  やり取りについてのログが欲しいです。
   -  log/ディレクトリの中に何についての実装をしたのか、どういう経緯でどのような機能を追加したのかなどまとめてください。

# 通知設定(Stop / PreCompact フック)
上の「最初のお願い」にある音声・Windows通知・コンテキスト警告は、`~/.claude/settings.json`(全プロジェクト共通)のStop/PreCompactフックと`~/.claude/hooks/claude-notify.ps1`で実装済み(2026-09-09)。フックはこのCLAUDE.mdを毎回読みに来るので、下の値を書き換えれば次の通知から反映される(再起動不要)。

- stop_sound: Asterisk
- stop_message: 実装が完了しました
- precompact_sound: Exclamation
- precompact_message: コンテキストの使用率が高くなっています。まもなく要約(compact)されます。

使用できる音(`stop_sound`/`precompact_sound`): Asterisk, Beep, Exclamation, Hand, Question。`stop_message`/`precompact_message`はトースト通知本文の自由記述(1行)。
なお、コンテキスト警告はClaude Codeのフックに使用率(%)を直接取得する仕組みが無いため、自動要約(auto compact)が発生する直前を検知して知らせる形になっている。

この設定の実体(`~/.claude/settings.json`・`~/.claude/hooks/claude-notify.ps1`)はリポジトリの外(Windowsのユーザープロファイル、Cドライブ)にあるためgit管理されない。他のPCへ引き継ぐための手順・コピーは`Document/引継ぎ_setup/`にまとめてある。

# リポジトリ構成
- `dev/ogawa/` — 友人(小川)が書いた車両シミュレーターのC実装一式。現状これがリポジトリ内で唯一のコード資産で、ゲームの描画・入力側(UI)はまだ存在しない。
- `doc/` — 要件・設計メモ。コードより先にこちらを読むと意図が掴みやすい。
  - `youken.txt` / `senba.txt` / `ogawa.txt` — ゲーム側(`padManager`/`moveManager`/`zundaManager`などによる入力受付・移動計算・ズンダもん描画)の設計スケッチ。`dev/ogawa/`のC実装とは別レイヤーの構想であり、対応する実装はまだリポジトリに無い。
  - `要素開発メモ.txt` — `dev/ogawa/src/apl`層(pperm/psysctl等)の役割分担を検討した生の思考ログ。各モジュールの仕様の一次情報はここにある。
  - `*.xlsx` — 小川氏側のたたき台スプレッドシート(未パース)。
- `log/devlog.txt` — 小川さん(および他の関係者)も使っている可能性がある共有の開発ログ(Shift-JIS)。**Claudeはここには書き込まない**。
- `log/claude_devlog.txt` — Claude Code専用の開発ログ(UTF-8、devlog.txtとは別ファイル)。上記「最初のお願い」に対応し、実装がひと区切りするたびに何を・なぜ・どう変えたかをここに追記する。
- `Document/引継ぎ_setup/` — Claude Codeの通知フック設定(実体はリポジトリ外の`~/.claude/`配下)を他のPCへ引き継ぐための手順書と設定ファイルのコピー。

# ビルド (`dev/ogawa/`)
- `cd dev/ogawa && make` でビルドし `build/simulator.exe` を生成。`make clean` / `make rebuild` あり。テストコマンドは無い(テストフレームワーク未導入)。
- Makefileのレシピは `if exist` / `mkdir` / `rmdir /S /Q` などcmd.exe組み込みコマンドを使っている前提。Git BashやPowerShellからは素の `make` ではなく、Windows版make(mingw32-make等)経由で叩く必要がある。**このマシンには2026-09-09時点でgcc/makeともに未インストール(Git Bash・PowerShellどちらのPATHにも無し)**なので、ビルドを頼まれたら先にツールチェーンの有無を確認すること。
- `SRCS`/`OBJS` は手動列挙方式で、`src/`配下の実ファイルより古い。例えば `apl/psysctl/psysctl.c`・`apl/aplaramng/aplaramng.c`・`apl/pio/pperm.c`・`sim/simaramng/simaramng.c` はソースツリーに存在するがMakefile未登録でビルド対象外。新規/既存モジュールをビルドに含めるときは `SRCS` と `OBJS` の両方に手で追記する。
- 実行エントリは `debug/kensa_1/main.c` の `main()`。中身は `env/swift_env` のループを起動して延々ログを出すだけの検査(kensa)用ハーネスで、ゲームUIではない。

# アーキテクチャ
車載ソフト(AUTOSAR的レイヤー分割)を模した設計で、4ms/16ms/64msの周期実行がベース。

## 実行フロー
1. `debug/kensa_1/main.c: main()` → `env/swift_env.c: vdgVirtualenvInit()` → `vdgVirtualenvExecute()`
2. `swift_env` が実時間(Windows `GetTickCount`)を `conf.h` の `u16g_VIRTUAL_REAL_TIME_SCALE` で仮想時間に換算し、`while(1)` ループの中で4ms/16ms/64ms経過するたびに `bsw/bcyclemng` の `vdgBcyclemngif{4,16,64}ms{in,out}()` を直接呼ぶ。
3. `bcyclemng` が各周期イベントを sac→apl→sim 各層の集約モジュール(`sacaramng`/`aplaramng`/`simaramng`)へファンアウトする。
4. 各層の集約モジュールが自層内の個別モジュール(下記)を呼ぶ想定だが、**`aplaramng`と`simaramng`は実ファイル(`apl/aplaramng/aplaramng.c`, `sim/simaramng/simaramng.c`)がありながらMakefile未登録で、実際にリンクされるのは`debug/kensa_1/dmy_def.c`内の空スタブ版**。`sacaramng`だけは本実装がビルドに組み込まれており、`dmy_def.c`側の同名実装はコメントアウトして衝突を避けている。実装を追うときは「そのモジュールが本当にリンクされているか」を`Makefile`の`SRCS`で確認すること。
5. なお `bsw/bschedule.c`(`vdgBscheduleifIncall/Outcall`、4ms×4回ごとに16ms・16ms×4回ごとに64msを刻んで`bcyclemng`を呼ぶ本番向けスケジューラ)は実装済みだが、現状`main`経路はこれを一切呼ばず`swift_env`の自前タイマーを直接使っている。将来組み込み実機向けにする際の入れ替え候補と思われる。

## レイヤー(`dev/ogawa/`配下)
- `env/` — 実行環境の入口。OS依存(Windows API)のリアルタイム→仮想時間変換とメインループ。
- `src/bsw/`(Basic SoftWare) — 周期スケジューラ`bschedule`、周期ファンアウト`bcyclemng`、生I/O境界`bios2bsw`(入力側)/`bbsw2ios`(出力側。現状ほぼ変数宣言のみ)。未着手モジュールは`【未】bbswrst/`に隔離されている。
- `src/sac/`(Sensor/Actuator Control) — ペダル・スイッチ単位の補正モジュール群: `sacelcrt`(アクセル)/`sbrkcrt`(ブレーキ)/`sclthcrt`(クラッチ)/`sgearcrt`(ギア)/`sigswcrt`(イグニッション)、および車速・回転数・状態確定系(`avel`/`arpmcfm`/`agearcfm`/`acfmsts`/`avehsts`)。
- `src/apl/`(アプリ層=業務ロジック/調停) — `pperm`(許可・シフト遷移・上限値の調停)、`pprtct`(オーバーレブ/クラッチ焼付/ブレーキ焼付/エンスト保護判定)、`pwarn`(オーバーヒート・センサー異常の警告通知)、`psysctl`(pperm調停結果を最終ギア・アクセル等としてSIMへ渡す)、`psimbrdg`(APL⇔SIM間の橋渡し変数)、`pvehstsjdg`(SIM側状態からStop/Run/SpeedUp/SpeedDown/Enstを判定)。この層の設計意図・変数一覧は`doc/要素開発メモ.txt`に詳しい。
- `src/sim/` — 車両物理シミュレーション本体: `mvirtmach`(全体を束ねる仮想マシン)、`meng`(エンジン)、`mgearbox`、`mclth`(クラッチ)、`mbrake`。
- `src/conf/conf.h` — 唯一の設定ファイル。`MACHINE_TYPE`(現状`MACHINE_TYPE_IOS`。名前と裏腹に単に素のC型を使う分岐で、他のmachine種別は未実装のプレースホルダ)、`PRINT_LOG_SETTING_CONF`(全モジュール共通のログON/OFF)、`u16g_VIRTUAL_REAL_TIME_SCALE`(実ms→仮想時間の分周比)。
- `src/inc/common.h` — 型定義(`<stdint.h>`を使わず独自typedef)、`stflag8`/`stflag16`ビットフラグ構造体、`ON/OFF/HI/LO/TRUE/FALSE`と各幅の`_MAX`/`_MIN`マクロ。`callib.h`はまだ中身の無いテンプレート。
- `template/template.c(.h)` — 新規モジュールのひな形。`external public variables` / `internal public variables` / `external function` / `internal function` のセクション見出しコメント構成に必ず従うこと。

## 命名規則(全モジュール共通。これを知らないとコードが読めない)
`[型プレフィックス][スコープ][モジュール名][if][用途]` というハンガリアン記法で統一されている。
- 型プレフィックス: `u8`/`u16`/`u32`(unsigned)、`s8`/`s16`/`s32`(signed)、`vd`(void)
- スコープ文字: `g`=グローバル(そのモジュールの`<module>if.h`で宣言される外部公開)、`s`=モジュール内static、`t`=関数内ローカル変数。変数名末尾の`O`=前回値を保持するstatic(例: `u8sSacelcrtThlpctO`)。
- モジュール名はPascalCaseでスコープ文字の直後に埋め込む(例: `Bschedule`, `Sacelcrt`, `Pperm`)。
- 層をまたいで公開する識別子はモジュール名の直後に`if`が付く。対応するヘッダは`<module>if.h`(例: `vdgSacelcrtifInit`は`sacelcrtif.h`で宣言、`u8gPpermifSht`は`ppermif.h`で宣言)。
- 周期関数のサフィックス: `Init`(電源ON時初期化)、`4msin`/`4msout`、`16msin`/`16msout`、`64msin`/`64msout`。`bschedule`自身の呼び出し関数だけは一段上位の扱いで`Initcall`/`Incall`/`Outcall`と命名される。

# 既知の注意点
- Makefileの`SRCS`は実体より古い。「ファイルが存在する」≠「ビルド対象」なので、モジュールを調査・修正するときは必ずMakefileで実際にリンクされているか確認する(上記「実行フロー」4項も参照)。
- 一部ファイルは疑似コードのままC言語として壊れている。例えば`dev/ogawa/src/apl/psysctl/psysctl.c`は関数の外にif/elseブロックが浮いており、識別子に日本語(`スピード`,`ブレーキ`)が混在していてそのままではコンパイルできない(Makefile未登録なのもこれが一因と思われる)。ファイルの存在だけを見て「実装済み」と判断しない。
- `dev/ogawa/src/apl/pio/pperm.c`はディレクトリ名・ファイル名に反して中身は`pioif`(APL入出力インターフェース)モジュールのコードで、`apl/pperm/pperm.c`(本物のpperm実装)とは無関係な別モジュール。名前で早合点しないこと。
- `doc/`・`log/devlog.txt`はUTF-8ではなくShift-JISで保存されている。標準的な読み方だと文字化けするため、変換してから読む(例: PowerShellで`[System.IO.File]::ReadAllText(path, [System.Text.Encoding]::GetEncoding("shift_jis"))`)。`devlog.txt`は共有ファイルのためClaudeは編集しない(下記`claude_devlog.txt`を使う)。それ以外の既存ファイルへの追記時は元のエンコード(Shift-JIS)を保つか、ユーザーに確認してから移行する。`log/claude_devlog.txt`はUTF-8で作成した専用ログなので、この注意は当てはまらない(標準エディタでそのまま読める)。
- `dev/ogawa/build/`配下のオブジェクトファイル・`simulator.exe`・`error.log`は`.gitignore`が空のためgit管理下に入っている。ビルドすると`git status`に差分が出る点に注意。
