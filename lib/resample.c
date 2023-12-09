double resample3(double A, double B, double C, double d) {
  double id = 1 - d;
  double ab = (id*A) + (d*B);
  double bc = (id*B) + (d*C);
  return (id*ab) + (d*bc);
}

double resample3exg(double A, double B, double C, double d) {
  return resample3(
    A,
    B*2 - ((A+C)/2),
    C,
    d
  );
}

double resample4(double A, double B, double C, double D, double d) {
  double id = 1 - d;
  return
    (id * resample3exg(A, B, C, 0.5+(d/2))) +
    ( d * resample3exg(B, C, D,      d/2 ));
}
