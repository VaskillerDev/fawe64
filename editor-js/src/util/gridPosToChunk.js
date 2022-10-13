const CHUNK_SIZE = 8;

export default function gridPosToChunk (gridPos) {
    return {x: Math.floor(gridPos.x / CHUNK_SIZE), y: Math.floor(gridPos.y / CHUNK_SIZE)}
}