// based on the example on https://www.npmjs.com/package/@abandonware/noble

const noble = require('@abandonware/noble');
const express = require('express')

const uuid_service = "1101"
// const uuid_value = ["2101", "2102", "2103", "2104", "2105", "2106"]
const uuid_value = ["2101", "2102", "2103"]


noble.on('stateChange', async (state) => {
  if (state === 'poweredOn') {
    
    console.log("start scanning")
    await noble.startScanningAsync([uuid_service], false);
  }
});

let accelerator;
noble.on('discover', async (peripheral) => {
  await noble.stopScanningAsync();
  await peripheral.connectAsync();
  const {characteristics} = await peripheral.discoverSomeServicesAndCharacteristicsAsync([uuid_service], uuid_value);
  accelerator = characteristics;
});


// read data periodically
//
let readData = async (characteristic) => {
  if(!characteristic) {
    return {};
  }

  const p0 = () => characteristic[0].readAsync();
  const p1 = () => characteristic[1].readAsync();
  const p2 = () => characteristic[2].readAsync();
  const p3 = () => characteristic[3].readAsync();
  const p4 = () => characteristic[4].readAsync();
  const p5 = () => characteristic[5].readAsync();

  
  // const [axValue, ayValue, azValue, gxValue, gyValue, gzValue] = await Promise.all([p0(), p1(), p2(), p3(), p4(), p5()]);
  const [axValue, ayValue, azValue, gxValue, gyValue, gzValue] = await Promise.all([p0(), p1(), p2()]);

  const sensorValues = {
    ax: axValue.readFloatLE(0),
    ay: ayValue.readFloatLE(0),
    az: azValue.readFloatLE(0),
    // gx: gxValue.readFloatLE(0),
    // gy: gyValue.readFloatLE(0),
    // gz: gzValue.readFloatLE(0),
  };

  return sensorValues;
}


const app = express()
const port = 3000


app.get('/', async(req, res) => {
  const value = await readData(accelerator);
  res.end(JSON.stringify(value));
});


app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})