<#
    start_mon.ps1 - cl 物理闭环监听启动器（run.md step3 标准启动方式）
    ================================================================
    封装"杀旧监听 -> 后台启动 -> 一次性探活"三步为一行调用：
    避免每次手工组装超长命令、避免前台同步启动阻塞、绕开 python3.bat 长参数拆参。
    注意：本文件带 UTF-8 BOM（PowerShell 7 下无 BOM 亦可正常解析；保留 BOM 为兼容
    旧 5.1 shell/手动终端，勿手改回无 BOM——PS5.1 无 BOM 按 ANSI 解码会破坏中文）。

    用法（在工程根执行）：
        & .cl/capture/start_mon.ps1 -Port COM5 -Baud 115200 -Watch 'ADC_READY' -Boot 'System Ready'
        & .cl/capture/start_mon.ps1 -Type can -Watch 'ready' -Boot 'boot'
        # 不带判据时仅常驻记录：-Watch 留空即可

    参数：
        -Type      uart | can             (默认 uart)
        -Port      UART 端口 (COM5)
        -Baud      UART 波特率 (默认 115200)
        -Chan      CAN 通道 (默认 PCAN_USBBUS1)
        -Watch     判据 regex，|| 分隔；含特殊字符用单引号包住
        -Boot      启动横幅 regex
        -Root      工程根 (默认 $PWD)
        -Tools     技能 tools 目录 (默认自动探测: CL_SKILL_ROOT > $PSScriptRoot 向上找 > 回退 E:/Desktop/XM/cl_skill)
        -KillOnly  只杀旧监听不启动 (排障用)

    说明：
        · 启动实际交给 serial_monitor.py/can_monitor.py --daemon（其内部分离进程 + 探活，
          调用方立即返回），本脚本负责杀掉旧监听释放端口、探测 python 直启路径，
          避免 python3.bat 转发长 regex 被拆参。
        · 启动后用 --daemon 一次探活；仍失败按 details/run-fault.md「监听重开规范」处理。
    #>

param(
    [string]$Port = "",
    [int]$Baud = 115200,
    [ValidateSet("uart", "can")]
    [string]$Type = "uart",
    [string]$Chan = "PCAN_USBBUS1",
    [string]$Watch = "",
    [string]$Boot = "",
    [string]$Root = "",
    [string]$Tools = "",
    [switch]$KillOnly
)

$ErrorActionPreference = "Stop"

# ---------- 1. 定位工程根与技能 tools ----------
if (-not $Root) { $Root = $PWD }
$cap = Join-Path $Root ".cl\capture"
if (-not (Test-Path -LiteralPath $cap)) { New-Item -ItemType Directory -Path $cap | Out-Null }

if (-not $Tools) {
    if ($env:CL_SKILL_ROOT -and (Test-Path -LiteralPath (Join-Path $env:CL_SKILL_ROOT "tools\serial_monitor.py"))) {
        $Tools = $env:CL_SKILL_ROOT
    } else {
        $probe = $PSScriptRoot
        while ($probe) {
            if (Test-Path -LiteralPath (Join-Path $probe "tools\serial_monitor.py")) { $Tools = $probe; break }
            $parent = Split-Path -Parent $probe
            if ($parent -eq $probe) { $probe = $null } else { $probe = $parent }
        }
    }
}
if (-not $Tools) {
    $fallback = "C:/Users/admin/Desktop/XM/SESkill/cl"
    if (Test-Path -LiteralPath (Join-Path $fallback "tools\serial_monitor.py")) { $Tools = $fallback }
}
if (-not $Tools) { Write-Error "无法定位 cl 技能 tools 目录（设 CL_SKILL_ROOT 或传 -Tools）"; exit 2 }

# ---------- 2. 杀旧监听释放端口 ----------
Get-CimInstance Win32_Process -Filter "Name='python.exe'" -ErrorAction SilentlyContinue |
    Where-Object { $_.CommandLine -match 'serial_monitor|can_monitor' } |
    ForEach-Object { Stop-Process -Id $_.ProcessId -Force -ErrorAction SilentlyContinue }
if ($KillOnly) { Write-Host "已清理旧监听进程"; exit 0 }

# ---------- 3. 探测 python 直启路径（避开 python3.bat 拆参） ----------
$py = $null
if (Get-Command python -ErrorAction SilentlyContinue) { $py = "python" }
elseif (Test-Path -LiteralPath "E:\qp\qtools\mingw32\opt\bin\python3.exe") { $py = "E:\qp\qtools\mingw32\opt\bin\python3.exe" }
elseif (Get-Command python3 -ErrorAction SilentlyContinue) { $py = (Get-Command python3).Source }
else { Write-Error "未找到 python/python3 解释器"; exit 2 }

# ---------- 4. 组装并启动（--daemon 内部分离+探活，立即返回） ----------
$mon = Join-Path $Tools "tools\serial_monitor.py"
$status = Join-Path $cap "status"
$marker = Join-Path $cap "flash_marker"
$out = Join-Path $cap "capture.log"

$baseArgs = @("$mon", "--duration", "0", "--timestamps", "--output", "$out",
    "--status", "$status", "--marker", "$marker", "--daemon")
if ($Type -eq "can") {
    $mon = Join-Path $Tools "tools\can_monitor.py"
    $baseArgs[0] = $mon
    $baseArgs += @("--channel", "$Chan", "--id", "0")
} else {
    if (-not $Port) { Write-Error "UART 模式需 -Port COMx"; exit 2 }
    $baseArgs += @("--port", "$Port", "--baud", "$Baud")
}
if ($Watch) { $baseArgs += @("--watch", $Watch) }
if ($Boot)  { $baseArgs += @("--boot", $Boot) }

Write-Host "[start_mon] 启动 $($Type.ToUpper()) 监听 (py=$py)"
& $py @baseArgs
if ($LASTEXITCODE -ne 0) {
    Write-Host "[start_mon] 启动失败（rc=$LASTEXITCODE），按 run-fault.md 排查：探活看 mon_err.log / 端口占用先杀旧监听 / 串口半死态断电重启"
    exit 1
}
exit 0
