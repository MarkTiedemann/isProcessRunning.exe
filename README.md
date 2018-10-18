# isProcessRunning.exe

```
Usage: isProcessRunning.exe <pid>
```

## Examples

```
$ isProcessRunning 0
true
```

```
$ isProcessRunning 9999999
false
```

## Spec

- If the specified process is running, `true` is printed to `stdout` and the programs exits with code `0`.
- If the specified process is not running, `false` is printed to `stdout` and the program exits with code `0`.
- If a usage error occurs, the usage is printed to `stderr` and the program exits with code `1`.
- If an unexpected error occurs, an error message is printed to `stderr` and the program exits with code `1`.

## Development

- **Install dependencies:** <code><a href="https://scoop.sh/">scoop</a> install visualc rktools2k3</code>
- **Build binary**: <code><a href="https://msdn.microsoft.com/en-us/library/610ecb4h.aspx">cl</a> isProcessRunning.cpp</code>
- **Test binary**: `powershell -f test.ps1`

## License

MIT
