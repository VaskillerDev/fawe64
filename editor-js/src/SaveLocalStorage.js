import {CHUNK_LEN_IN_MAP} from "./GridViewGl";

export default function SaveLocalStorage() {
    const map = {};
    
    for (let i = 0; i < CHUNK_LEN_IN_MAP; i++) {
        for (let j = 0; j < CHUNK_LEN_IN_MAP; j++) {
            map[`${i}:${j}`] = localStorage.getItem(`${i}:${j}`);
        }
    }
    
    return JSON.stringify(map);
}