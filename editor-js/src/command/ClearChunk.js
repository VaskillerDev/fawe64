const CLEAR_CHUNK = "-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1";

export default function ClearChunk(chunkPosX, chunkPosY) {
    window.localStorage.setItem(`${chunkPosX}:${chunkPosY}`,CLEAR_CHUNK);
    
    const startLocalPosX = chunkPosX * 8;
    const startLocalPosY = chunkPosY * 8;
    const endLocalPosX = startLocalPosX + 8;
    const endLocalPosY = startLocalPosY + 8;
    
    for (let x = startLocalPosX; x < endLocalPosX; x++) {
        for (let y = startLocalPosY; y < endLocalPosY; y++) {
            window.localStorage.removeItem(`rock:${x}:${y}`)
        }
    }
    
    
    window.location.reload()
}