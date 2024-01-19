export async function cleanEval(code) {
  // todo: maybe use "vm" instead of eval
  await eval(code);
}