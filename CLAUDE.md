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

# ブランチ構成(2026-09-09~)
最終目標がUE5でのゲーム制作であり、現状のC実装(小川さんの意思の入った途中成果物)をClaudeの実装で不可逆に変えてしまわないよう、以下の体制にしている。
- `main` / `nanamaru/work` — 小川さんからの引き継ぎ+ドキュメント整備のみ。Claudeによる実装は積まれない。
- tag `ogawa-handoff-20260909` — Claudeが本格実装に着手する直前の状態を固定したバックアップ。
- `nanamaru/claude-impl` — Claudeによる実装(sim層の新規実装、apl層の修正等)はすべてこのブランチで行う。**このファイルが説明するアーキテクチャの現在地(sim層実装済み等)はこのブランチでの話**であり、`main`はまだ「経緯」節にある通りの中途半端な状態のまま。

# リポジトリ構成
- `dev/ogawa/` — 友人(小川)が書いた車両シミュレーターのC実装一式。現状これがリポジトリ内で唯一のコード資産で、ゲームの描画・入力側(UI)はまだ存在しない。
- `doc/` — 要件・設計メモ。コードより先にこちらを読むと意図が掴みやすい。
  - `youken.txt` / `senba.txt` / `ogawa.txt` — ゲーム側(`padManager`/`moveManager`/`zundaManager`などによる入力受付・移動計算・ズンダもん描画)の設計スケッチ。`dev/ogawa/`のC実装とは別レイヤーの構想であり、対応する実装はまだリポジトリに無い。
  - `要素開発メモ.txt` — `dev/ogawa/src/apl`層(pperm/psysctl等)の役割分担を検討した生の思考ログ。各モジュールの仕様の一次情報はここにある。
  - `*.xlsx` — 小川氏側のたたき台スプレッドシート(未パース)。
- `log/devlog.txt` — 小川さん(および他の関係者)も使っている可能性がある共有の開発ログ(Shift-JIS)。**Claudeはここには書き込まない**。
- `log/claude_devlog.txt` — Claude Code専用の開発ログ(UTF-8、devlog.txtとは別ファイル)。上記「最初のお願い」に対応し、実装がひと区切りするたびに何を・なぜ・どう変えたかをここに追記する。
- `Document/引継ぎ_setup/` — Claude Codeの通知フック設定(実体はリポジトリ外の`~/.claude/`配下)を他のPCへ引き継ぐための手順書と設定ファイルのコピー。

# ビルド (`dev/ogawa/`, `nanamaru/claude-impl`ブランチで動作確認済み)
- `cd dev/ogawa && make rebuild` でクリーンビルドし `build/simulator.exe` を生成。`make` / `make clean` もあり。テストコマンドは無い(自動テストフレームワーク未導入。代わりに下記kensa_seqの手動確認用シーケンスがある)。
- Makefileのレシピは `if exist` / `mkdir` / `rmdir /S /Q` などcmd.exe組み込みコマンドを使っている前提。**Git Bash(sh.exeがPATH上にある環境)から`make`を叩くとこれらのcmd構文でシンタックスエラーになる**。PowerShellまたはcmd.exeから実行すること。
- **ビルド環境(2026-09-09導入)**: WinLibs版 GCC 16.2.0 + MinGW-w64 を `E:\Program\mingw64\` にインストール済み(インストーラーなし、フォルダ展開のみ。Cドライブには置いていない)。`bin`直下に`gcc.exe`と`mingw32-make.exe`があり、`make.exe`は`mingw32-make.exe`のコピーとして追加してあるので`make`/`mingw32-make`どちらでも呼べる。ユーザー環境変数PATHに`E:\Program\mingw64\bin`を追加済みだが、**追加前から開いていたシェル/セッションには反映されない**(Windowsの仕様上、新しいターミナルを開くかサインインし直すまで古いPATHのまま)。反映されていない場合は`E:\Program\mingw64\bin\gcc.exe`のようにフルパスで呼ぶか、そのセッション内で`PATH`にこのフォルダを一時的に追加すること。
- `SRCS`/`OBJS`は手動列挙方式。2026-09-09時点で`sim/`配下の全モジュール、`apl/psysctl`、`apl/aplaramng`は追加済みでビルドに含まれる。`apl/pio/`だけは意図的に未登録のまま(下記「既知の注意点」参照)。新規モジュールを追加する際は`SRCS`と`OBJS`の両方に手で追記し、対応するコンパイルルールも追加すること。
- 実行エントリは `debug/kensa_1/main.c` の `main()`。`env/swift_env`のループを起動し、`debug/kensa_1/kensa_seq.c`(擬似入力シーケンス、下記参照)が車を実際に走らせて動作確認できるようにしている。まだゲームUIではない(コンソール出力のみ)。

# アーキテクチャ
車載ソフト(AUTOSAR的レイヤー分割)を模した設計で、4ms/16ms/64msの周期実行がベース。

## 実行フロー
1. `debug/kensa_1/main.c: main()` → `env/swift_env.c: vdgVirtualenvInit()` → `vdgVirtualenvExecute()`
2. `swift_env` が実時間(Windows `GetTickCount`)を `conf.h` の `u16g_VIRTUAL_REAL_TIME_SCALE` で仮想時間に換算し、`while(1)` ループの中で4ms/16ms/64ms経過するたびに `bsw/bcyclemng` の `vdgBcyclemngif{4,16,64}ms{in,out}()` を直接呼ぶ。
3. `bcyclemng` が各周期イベントを sac→apl→sim 各層の集約モジュール(`sacaramng`/`aplaramng`/`simaramng`)へファンアウトする。
4. 各層の集約モジュール(`sacaramng`/`aplaramng`/`simaramng`)が自層内の個別モジュールを呼ぶ。2026-09-09時点で3つともMakefileに組み込み済み・実装済みで、`debug/kensa_1/dmy_def.c`内の対応スタブはコメントアウトして衝突を避けている(新しい集約モジュールを追加/復活させる場合は同じパターンで対応するダミー実装をコメントアウトすること。忘れるとシンボル重複でリンクエラーになる)。
5. なお `bsw/bschedule.c`(`vdgBscheduleifIncall/Outcall`、4ms×4回ごとに16ms・16ms×4回ごとに64msを刻んで`bcyclemng`を呼ぶ本番向けスケジューラ)は実装済みだが、現状`main`経路はこれを一切呼ばず`swift_env`の自前タイマーを直接使っている。将来組み込み実機向けにする際の入れ替え候補と思われる。

## レイヤー(`dev/ogawa/`配下)
- `env/` — 実行環境の入口。OS依存(Windows API)のリアルタイム→仮想時間変換とメインループ。
- `src/bsw/`(Basic SoftWare) — 周期スケジューラ`bschedule`、周期ファンアウト`bcyclemng`、生I/O境界`bios2bsw`(入力側)/`bbsw2ios`(出力側。現状ほぼ変数宣言のみ)。未着手モジュールは`【未】bbswrst/`に隔離されている。
- `src/sac/`(Sensor/Actuator Control) — ペダル・スイッチ単位の補正モジュール群: `sacelcrt`(アクセル)/`sbrkcrt`(ブレーキ)/`sclthcrt`(クラッチ)/`sgearcrt`(ギア)/`sigswcrt`(イグニッション)、および車速・回転数・状態確定系(`avel`/`arpmcfm`/`agearcfm`/`acfmsts`/`avehsts`)。
- `src/apl/`(アプリ層=業務ロジック/調停) — `pperm`(許可・シフト遷移・上限値の調停)、`pprtct`(オーバーレブ/クラッチ焼付/ブレーキ焼付/エンスト保護判定)、`pwarn`(オーバーヒート・センサー異常の警告通知)、`psysctl`(pperm調停結果を最終ギア・アクセル等としてSIMへ渡す)、`psimbrdg`(APL⇔SIM間の橋渡し変数)、`pvehstsjdg`(SIM側状態からStop/Run/SpeedUp/SpeedDown/Enstを判定)。この層の設計意図・変数一覧は`doc/要素開発メモ.txt`に詳しい。
- `src/sim/`(2026-09-09にゼロから新規実装。それ以前は全ファイルが空テンプレートだった) — 車両物理シミュレーション本体、4msサイクルで積分する簡易モデル: `mclth`(クラッチ結合率=ペダル開度の反転)→`mgearbox`(ギア段数から線形の速度⇔回転数比・駆動定数を算出)→`meng`(ホイール由来回転数とアクセルに応じたフリーレブ回転数をクラッチ結合率でブレンドし、スルーレート制限付きで追従させるエンジン回転数モデル。停止+ギアイン+クラッチ接続+アクセル0で自然にエンストが再現される)→`mbrake`(ペダル開度に比例した減速)の順に`mvirtmach`(全体を束ねる仮想マシン。駆動力=アクセル×クラッチ結合率×ギア定数から速度を積分)が呼ぶ。ギア比・質量・空気抵抗相当などの定数は全て仮の調整値(要チューニング、コード内に明記)。
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
- `dev/ogawa/src/apl/pio/pperm.c`はディレクトリ名・ファイル名に反して中身は`pioif`(APL入出力インターフェース)モジュールのコードで、`apl/pperm/pperm.c`(本物のpperm実装)とは無関係な別モジュール。しかも対応するはずの`pioif.h`は別モジュール(`pvehstsjdgif.h`)のバイト単位コピペという致命的な状態で、.c側もincludeすらしていない。**意図的に未修正・Makefile未登録のまま放置している**(`psysctl`/`psimbrdg`が同等の役割を既に果たしており、復活させると重複した第三の集約層になるだけと判断したため)。名前で早合点しないこと。
- `apl/*if.h`ヘッダ群(`ppermif.h`,`pprtctif.h`,`pwarnif.h`,`psimbrdgif.h`,`pvehstsjdgif.h`,`psysctlif.h`)は自己完結化のため`../inc/common.h`を自前でincludeするようにしてある(2026-09-09修正。元は呼び出し側が先にcommon.hをincludeしている前提で、`sacaramng.c`や`avehsts.c`など離れた場所からこれらのヘッダを辿るchainに入ると`uint8_t`等が未定義でコンパイルエラーになっていた)。新しいapl系ヘッダを作るときも同様に自己完結にすること。同じ理由で`debug/log/print_log.h`にも`common.h`のincludeを追加済み。
- **sim層の物理定数はすべて仮の調整値**(コード内コメントに明記)。特に`pperm.c`のシフト許可条件は仕様書(`doc/要素開発メモ.txt`)の「通常シフトも車速5km以上」という記載をそのまま実装すると、停止状態から1速に入れられず永久に発進できないデッドロックになることが判明したため、通常シフトの車速条件は外してある(リバースの車速5km以下条件はそのまま)。同様に`pprtct.c`のエンスト判定は、イグニッションONの瞬間(エンジン始動直後で回転数がまだ0)を誤検知しないよう、低回転が一定時間(仮想約240ms)継続した場合のみ検知するようにしてある。この手の「個々のモジュールは正しく見えても組み合わせるとデッドロックする」パターンは今後も要注意。
- `env/swift_env/swift_env.c`の`#else`(`PRINT_LOG_SETTING_CONF`をUNVALIDにした場合)分岐は`vdsVirtualtimeUpdateDm()`が中身`T.B.D`の空スタブ、`vdsVirtualtimeDmCounter()`は引数リストに構文エラー(`void 9`)がある。**ログ設定を無効にすると実質的に仮想時間が一切進まなくなり、かつビルドも通らない**。おそらく非Windows移植を見据えた未着手のフックなので、意図的に手を付けていない(現状`PRINT_LOG_SETTING_CONF`は常にVALID運用)。
- `debug/kensa_1/kensa_seq.c`/`kensa_seq.h`(2026-09-09新規)は実キーボード/ゲームパッド入力が無い代わりに擬似的な運転シーケンス(IG-ON→発進→2回アップシフト→ブレーキ減速→停止→IG-OFF)を`bcyclemng`の64msフックから注入し、結果を`vdgLogArgPrint`で毎フレーム表示する検査ハーネス。この状態表示は`PRINT_LOG_SETTING_CONF`の詳細トレースとは独立に常時出力される。なお`PRINT_LOG_SETTING_CONF`をVALIDのまま長時間(kensa_seqの全21フレーム=仮想64ms×21≒実時間67秒超)実行すると、全モジュールの詳細ログ出力量(I/O)が原因とみられる理由で`swift_env`のリアルタイム→仮想時間換算の実測ペースが乱れる現象を確認している(シミュレーション自体のロジックには影響しない、あくまでコンソール出力が大量な場合の表示ペースの話)。
- `doc/`・`log/devlog.txt`はUTF-8ではなくShift-JISで保存されている。標準的な読み方だと文字化けするため、変換してから読む(例: PowerShellで`[System.IO.File]::ReadAllText(path, [System.Text.Encoding]::GetEncoding("shift_jis"))`)。`devlog.txt`は共有ファイルのためClaudeは編集しない(下記`claude_devlog.txt`を使う)。それ以外の既存ファイルへの追記時は元のエンコード(Shift-JIS)を保つか、ユーザーに確認してから移行する。`log/claude_devlog.txt`はUTF-8で作成した専用ログなので、この注意は当てはまらない(標準エディタでそのまま読める)。
- `dev/ogawa/build/`配下のオブジェクトファイル・`simulator.exe`・`error.log`は`.gitignore`が空のためgit管理下に入っている。ビルドすると`git status`に差分が出る点に注意。なお2026-08-02の初回コミット以来リビルドされていなかった古い`.o`が長期間残っていたため、「`.o`が存在する」ことはコンパイルが通る証拠にならない(実際、当時のソースは`pperm.c`のバグ等でビルドが通らない状態だった)。
