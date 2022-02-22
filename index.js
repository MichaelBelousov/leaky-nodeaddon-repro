
const { NativeObj, getInfo } = require('./build/Debug/native_test.node')

const formatter = new Intl.NumberFormat('en-US', {
  minimumFractionDigits: 1,
  maximumFractionDigits: 1,
});

function formatMem(bytes) {
  const megaBytes = bytes / (1024*1024);
  return formatter.format(megaBytes) + "MB";
}

async function main() {
  for (let i = 0; i < 10_000_000; ++i) {
    const nativeObj = getInfo();
    if (i % 10000 === 0) {
      console.log(`${i} iterations; rss: ${formatMem(process.memoryUsage().rss)}`);
    }
    // uncomment this and the application will not leak
    // await new Promise(setImmediate);
  }
}

main().catch(console.error);

