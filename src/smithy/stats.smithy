$version: "2"
namespace com.firebolt.stats

service StatsService {
    version: "1.0"
    operations: [memoryUsage]
}

operation memoryUsage {
    input: MemoryUsageInput
    output: MemoryUsageOutput
}

structure MemoryUsageInput {
}

structure MemoryUsageOutput {
    @required
    value: MemoryInfo
}

structure MemoryInfo {
    @required
    gpuMemoryLimit: Integer
    @required
    gpuMemoryUsed: Integer
    @required
    userMemoryLimit: Integer
    @required
    userMemoryUsed: Integer
}
