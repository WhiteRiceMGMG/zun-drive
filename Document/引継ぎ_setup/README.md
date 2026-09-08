# Claude Code 通知設定の引き継ぎ手順

zun-driveプロジェクトで使っているClaude Codeの通知機能(回答完了時の音・Windows通知、
コンテキスト使用率が高いときの警告)を、別のPCへ引き継ぐための資料一式です。

## 前提: 設定は2箇所に分かれている

| 内容 | 保存場所 | このリポジトリで管理されるか |
|---|---|---|
| zun-driveリポジトリ本体(コード・doc・log等) | プロジェクトフォルダ(例: `E:\Program\zun-drive\`) | される(git管理下) |
| Claude Codeの通知フック設定 | `%USERPROFILE%\.claude\`(Windowsのユーザープロファイル、**全プロジェクト共通**) | **されない**(リポジトリの外側) |

通知フックの実体は、このリポジトリとは無関係な場所(Windowsのユーザープロファイル配下)に
置かれています。そのため `git clone` / `git pull` をするだけでは新しいPCに引き継がれません。
このフォルダに設定の実体のコピーを保管しておくことで、リポジトリと一緒に引き継げるようにしています。

## このフォルダの中身

- `claude-notify.ps1` … 通知処理の本体(`~/.claude/hooks/claude-notify.ps1` のコピー)
- `hooks.snippet.json` … `~/.claude/settings.json` に追記する `hooks` 設定のコピー
- `README.md` … このファイル

## 新しいPCでのセットアップ手順(Windows専用)

1. このリポジトリをclone(またはpull)する。
2. `claude-notify.ps1` を新しいPCの次の場所にコピーする(`hooks`フォルダが無ければ作成する)。
   ```
   %USERPROFILE%\.claude\hooks\claude-notify.ps1
   ```
3. `hooks.snippet.json` の中身を、新しいPCの `%USERPROFILE%\.claude\settings.json` にマージする。
   - `settings.json` に `hooks` キーがまだ無ければ、そのままキーごと追記してよい。
   - 既に `hooks` キーがある場合は、既存の内容を消さずに `Stop` / `PreCompact` を追記する
     (`theme` や `model` など他の設定を上書きしないよう注意)。
4. Claude Codeを再起動する。反映されない場合は一度 `/hooks` を開く。

## 動作確認のしかた

PowerShellから直接スクリプトを実行して、音とWindows通知(画面右下)が出るか確認できます。

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%USERPROFILE%\.claude\hooks\claude-notify.ps1" -Event Stop
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%USERPROFILE%\.claude\hooks\claude-notify.ps1" -Event PreCompact
```

## 注意点

- `claude-notify.ps1` は `System.Media.SystemSounds` や `System.Windows.Forms` など
  Windows専用のAPIを使っています。**引き継ぎ先もWindows PCであることが前提**です。
  Mac/Linuxへ引き継ぐ場合は別実装が必要になります。
- 音・通知メッセージの内容は、プロジェクトごとの `CLAUDE.md` 内の次の値で調整できます
  (詳細は zun-drive の `CLAUDE.md` の「通知設定」セクションを参照)。
  - `stop_sound` / `stop_message` … 回答完了時の音・メッセージ
  - `precompact_sound` / `precompact_message` … コンテキスト使用率が高いときの音・メッセージ
  - 使用できる音: `Asterisk`, `Beep`, `Exclamation`, `Hand`, `Question`
- ここに置いている2ファイルは、実際に動いている `~/.claude/` 配下のファイルの**コピー**です。
  本体の設定を変更したら、このフォルダのコピーも忘れずに更新してください(自動同期はされません)。
- 開発ログについて: `log/devlog.txt` は小川さんも使う可能性がある共有ファイルのため、
  Claude Codeが書く実装ログは `log/claude_devlog.txt`(UTF-8)に分けて記録しています。
