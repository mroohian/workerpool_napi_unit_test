const path = require('path');
const workerpool = require('workerpool');

const main = async () => {
  const worker = path.join(__dirname, './worker.js');

  const pool = workerpool.pool(worker, {
    minWorkers: 1,
    maxWorkers: 1,
    workerType: 'process'
  });

  let i = 0;
  while (i < 3) {

    try {
      switch (i) {
        case 0:
          await pool.exec('normalMethod');
          break;
        case 1:
          await pool.exec('crashMethod');
          break;
        case 2:
          await pool.exec('normalMethod');
          break;
      }
    } catch (error) {
      console.error(`Error: ${error}`);
    }

    await new Promise((cb) => setTimeout(cb, 1000));

    i++;
    console.log('next: ', i)
  }
};

main().then(() => { console.log('done'); process.exit(0); });