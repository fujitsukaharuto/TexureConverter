$files = Get-ChildItem *.jpg, *.png
foreach ($f in $files) {
    Start-Process -FilePath TexureConverter.exe -ArgumentList $f -Wait
}
pause