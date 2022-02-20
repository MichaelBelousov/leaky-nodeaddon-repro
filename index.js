
const { NativeObj } = require("./build/Debug/native_test.node")

async function main() {
  for (let i = 0; i < 10_000_000; ++i) {
    const nativeObj = new NativeObj();
    if (i % 10000 === 0) {
      console.log(String(i) + " iterations, process memory at " + process.memoryUsage.rss);
    }
  }
}

main().catch(console.error)

