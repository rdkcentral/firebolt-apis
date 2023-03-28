export module Settings {
    type LogLevel = "WARN" | "INFO" | "DEBUG" | "ERROR"
    function setLogLevel(logLevel: LogLevel): void
    function getLogLevel(): LogLevel     
}

export module Log {
    function info(...args: any[]): void
    function debug(...args: any[]): void
    function error(...args: any[]): void
    function warn(...args: any[]): void
}

export module Events {
    function listen(...args: any[]): Promise<number>
    function once(...args: any[]): Promise<number>
    function clear(...args: any[]): boolean
}
