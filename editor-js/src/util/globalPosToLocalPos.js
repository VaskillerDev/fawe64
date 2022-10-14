export default function globalPosToLocalPos(chunkPos, gridPos) {
    return {x: gridPos.x - chunkPos.x * 8, y: gridPos.y - chunkPos.y * 8};
}