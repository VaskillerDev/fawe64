import * as fs from "fs";
import { argv } from 'process';

const FLG = new Int32Array(4);
FLG[0] = 0x80000000;
FLG[1] = 0x40000000;
FLG[2] = 0x20000000;
FLG[3] = ~(FLG[0] | FLG[1] | FLG[2]);

const content = fs.readFileSync(`../assets/${argv[2]}${argv[3]}${argv[4]}.csv`, {encoding: "ascii"});
const oneLineTiledMap = content.replace(/(\r\n|\n|\r)/gm,',');
let data = oneLineTiledMap.split(',')
data.pop();
data = data.map(e=>+e).map(translateData);

function translateData(d) {
    const d32 = new Int32Array(4);
    d32[0] = d; // data
    d32[1] = !!(d32[0] & FLG[0]) // fh
    d32[2] = !!(d32[0] & FLG[1]) // fv
    d32[3] = (d32[0] & FLG[3]) // id

    //console.log(`${d}: [h: ${d32[1]}, v: ${d32[2]}, id: ${d32[3] }]`);
    //console.log("value: ", 100 * d32[1] + 10 * d32[2] + d32[3]);

    return 100 * d32[1] + 10 * d32[2] + d32[3];
}

let dataStr = "";
data.forEach(d=>(dataStr+=d +','));
dataStr = dataStr.slice(0,-1);

const initArrayLiteral = `const uint8_t ${argv[2]}[${argv[3]}][${argv[4]}] = {${dataStr}}`

console.log(initArrayLiteral);
//console.log(oneLineTiledMap)