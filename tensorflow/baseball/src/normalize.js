
/**
 * Normalize a value between a given range.
 * 
 * @param {Float} value 
 * @param {Float} min 
 * @param {Float} max 
 * @returns {Float} normalized value
 */
export default function normalize(value, min, max) {
    if(min === undefined || max === undefined) {
        return value;
    }
    return (value - min) / (max - min);
}
  