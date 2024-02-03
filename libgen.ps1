param(
    [Parameter(Mandatory=$true)]
    [string] $dllInFilepath

    #[Parameter(Mandatory=$true)]
    #[string] $libOutFilepath
)

$moduleName = [io.path]::GetFileNameWithoutExtension($dllInFilepath) 
$exportsFilename = $moduleName + ".exports"

& dumpbin.exe /nologo /exports "$dllInFilepath" > $exportsFilename

$exportContent = Get-Content -Path ./$exportsFilename

#create a list of exported functions

$exports = New-Object System.Collections.Generic.List[string]
foreach ($line in $($exportContent -split "`r`n")) {
    if ($line -match "^\s*\d+\s+[0-9a-fA-F]+\s+(?:[0-9a-fA-F]+\s+)?(.+?)(?=\s+\(forwarded|\s*$)") {
        if (!$Matches[1].StartsWith("[")) {
            $exports.Add($Matches[1])
        }
    }
}

$moduleDefFilename = $moduleName + ".def"
$moduleDef = "EXPORTS`n"

foreach ($export in $exports) {
    $moduleDef += "$export`n"
}

Out-File -FilePath "./$moduleDefFilename" -InputObject $moduleDef

$libFilename = $moduleName + ".lib"

& lib.exe /nologo /def:$moduleDefFilename /MACHINE:x64 /out:$libFilename