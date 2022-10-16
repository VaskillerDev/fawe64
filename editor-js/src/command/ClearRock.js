export default function ClearRock(gridPosX, gridPosY) {
    window.localStorage.removeItem(`rock:${gridPosX}:${gridPosY}`)
    window.location.reload()
}