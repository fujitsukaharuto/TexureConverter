$files = Get-ChildItem *.jpg, *.png
foreach ($f in $files) {
     $args = @(
        $f,  # ファイルパス
        "-ml", "0"    # オプションをここに追加
    )
    Start-Process -FilePath TexureConverter.exe -ArgumentList $args -Wait
}
pause