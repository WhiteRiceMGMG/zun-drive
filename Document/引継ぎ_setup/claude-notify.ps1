# claude-notify.ps1
# Plays a sound and shows a Windows toast (balloon tip) notification for Claude Code hooks.
# Usage: powershell.exe -NoProfile -ExecutionPolicy Bypass -File claude-notify.ps1 -Event Stop|PreCompact
#
# The sound/message used can be overridden per-project by adding lines like the following
# to that project's CLAUDE.md (plain "key: value" lines, anywhere in the file):
#   stop_sound: Asterisk
#   stop_message: Your custom completion message
#   precompact_sound: Exclamation
#   precompact_message: Your custom context-warning message
# Valid sound names: Asterisk, Beep, Exclamation, Hand, Question
# If no override is found, built-in defaults below are used.

param(
    [ValidateSet("Stop", "PreCompact")]
    [string]$Event = "Stop"
)

$ErrorActionPreference = "SilentlyContinue"

if ($Event -eq "Stop") {
    $soundKey = "stop_sound"
    $msgKey = "stop_message"
    $defaultSound = "Asterisk"
    $defaultMessage = "Claude finished responding."
    $title = "Claude Code"
} else {
    $soundKey = "precompact_sound"
    $msgKey = "precompact_message"
    $defaultSound = "Exclamation"
    $defaultMessage = "Context window is nearly full; auto-compact is about to run."
    $title = "Claude Code - Context Warning"
}

$sound = $defaultSound
$message = $defaultMessage

# Look for a CLAUDE.md that overrides the defaults: project dir env var, then cwd, then global.
$candidates = New-Object System.Collections.Generic.List[string]
if ($env:CLAUDE_PROJECT_DIR) {
    $candidates.Add((Join-Path $env:CLAUDE_PROJECT_DIR "CLAUDE.md"))
}
try {
    $candidates.Add((Join-Path (Get-Location).Path "CLAUDE.md"))
} catch { }
if ($env:USERPROFILE) {
    $candidates.Add((Join-Path $env:USERPROFILE ".claude/CLAUDE.md"))
}

foreach ($path in $candidates) {
    if ($path -and (Test-Path -LiteralPath $path -PathType Leaf)) {
        $text = $null
        try {
            $text = [System.IO.File]::ReadAllText($path, [System.Text.Encoding]::UTF8)
        } catch { }

        if ($text) {
            $soundMatch = [regex]::Match($text, "$soundKey\s*:\s*(\S+)")
            $msgMatch = [regex]::Match($text, "$msgKey\s*:\s*(.+)")

            if ($soundMatch.Success) { $sound = $soundMatch.Groups[1].Value.Trim() }
            if ($msgMatch.Success) { $message = $msgMatch.Groups[1].Value.Trim() }

            if ($soundMatch.Success -or $msgMatch.Success) { break }
        }
    }
}

$soundObj = switch ($sound) {
    "Asterisk"    { [System.Media.SystemSounds]::Asterisk }
    "Beep"        { [System.Media.SystemSounds]::Beep }
    "Exclamation" { [System.Media.SystemSounds]::Exclamation }
    "Hand"        { [System.Media.SystemSounds]::Hand }
    "Question"    { [System.Media.SystemSounds]::Question }
    default       { [System.Media.SystemSounds]::Asterisk }
}

try { $soundObj.Play() } catch { }

try {
    Add-Type -AssemblyName System.Windows.Forms
    Add-Type -AssemblyName System.Drawing

    $notifyIcon = New-Object System.Windows.Forms.NotifyIcon
    $notifyIcon.Icon = [System.Drawing.SystemIcons]::Information
    $notifyIcon.Visible = $true
    $notifyIcon.BalloonTipTitle = $title
    $notifyIcon.BalloonTipText = $message
    $notifyIcon.ShowBalloonTip(5000)

    Start-Sleep -Milliseconds 4000
    $notifyIcon.Dispose()
} catch { }
