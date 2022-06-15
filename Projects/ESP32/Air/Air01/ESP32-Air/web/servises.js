function getColorForPercentage(pct, low, middle, up,
    color_low_r, color_low_g, color_low_b,
    color_middle_r, color_middle_g, color_middle_b,
    color_up_r, color_up_g, color_up_b) {
    var percentColors = [
        { pct: low, color: { r: color_low_r, g: color_low_g, b: color_low_b } },
        { pct: middle, color: { r: color_middle_r, g: color_middle_g, b: color_middle_b } },
        { pct: up, color: { r: color_up_r, g: color_up_g, b: color_up_b } }]

    for (var i = 1; i < percentColors.length - 1; i++) {
        if (pct < percentColors[i].pct) {
            break
        }
    }
    var lower = percentColors[i - 1]
    var upper = percentColors[i]
    var range = upper.pct - lower.pct
    var rangePct = (pct - lower.pct) / range
    var pctLower = 1 - rangePct
    var pctUpper = rangePct
    var color = {
        r: Math.floor(lower.color.r * pctLower + upper.color.r * pctUpper),
        g: Math.floor(lower.color.g * pctLower + upper.color.g * pctUpper),
        b: Math.floor(lower.color.b * pctLower + upper.color.b * pctUpper)
    }
    return [color.r, color.g, color.b].join(',')
}