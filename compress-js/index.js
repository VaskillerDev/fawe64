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
    const d32 = new Int32Array(5);
    d32[0] = d; // data
    d32[1] = !!(d & FLG[0]) // fh
    d32[2] = !!(d & FLG[1]) // fv
    d32[3] = !!(d & FLG[2]) // fd
    d32[4] = (d & FLG[3]) // id

    console.log(`${d}: [h: ${d32[1]}, v: ${d32[2]}, d: ${d32[3]} id: ${d32[4] }]`);
    console.log("value: ",  100 * d32[1] + 10 * (d32[2] + (d32[3] * 2)) + d32[4]);

    /**
     * TODO: этот всратый формат трактуется так, поскольку мы можем себе позволить только 8 битные числа
     * Каждый тайл состоит из трех десятичных разрядов. Далее от старшего к младшему:
     *  <1=горизонтальный поворот>
     *  <1=вертикальный поворот | 2= диагональный поворот | 3 =диагональный и вертикальный поворот>
     *  <число= id тайла>
     *   Таким образом, к примеру:
     *   131 == тайл с горизонтальным,диагональным и вертикальным поворотом с id 1
     *   103 == тайл с горизонтальным поворотом и id 3
     *   22 == тайл с диагональным  поворотом с id 2
     *   12 == тайл с вертикальным поворотом с id 2
     *   2 == просто тайл с id 2
     */
    return 100 * d32[1] + 10 * (d32[2] + (d32[3] * 2)) + d32[4];
}

let dataStr = "";
data.forEach(d=>(dataStr+=d +','));
dataStr = dataStr.slice(0,-1);

const initArrayLiteral = `const uint8_t ${argv[2]}[${argv[3]}][${argv[4]}] = {${dataStr}}`

console.log(initArrayLiteral);
//console.log(oneLineTiledMap)