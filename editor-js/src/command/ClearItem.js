export default function ClearItem(gridPosX, gridPosY) {
    window.localStorage.removeItem(`item:${gridPosX}:${gridPosY}`)
    window.location.reload()
}