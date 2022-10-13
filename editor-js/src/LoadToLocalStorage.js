import {CHUNK_LEN_IN_MAP} from "./GridViewGl";

export default function LoadToLocalStorage(mapString) {
    const map = JSON.parse(mapString);

    for (let i = 0; i < CHUNK_LEN_IN_MAP; i++) {
        for (let j = 0; j < CHUNK_LEN_IN_MAP; j++) {
            localStorage.setItem(`${i}:${j}`,map[`${i}:${j}`] );
        }
    }

    window.location.reload();
}