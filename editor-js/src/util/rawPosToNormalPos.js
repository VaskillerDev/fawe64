export default function rawPosToNormalPos(rawPos) {
    const lastChar = rawPos.length-1;
    if (!(rawPos.charAt(0) === '(' && rawPos.charAt(lastChar) === ')')) return;

    let pos = rawPos.substring(1, lastChar).split(';');
    return {x: Number.parseInt(pos[0]), y: Number.parseInt(pos[1])};
}