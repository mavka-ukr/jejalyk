function a() {
  return b();
}

function b() {
  const x = a();
  return 1;
}