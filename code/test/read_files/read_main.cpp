
float** read_kinetisense(const char path[]);

  int main() {

  float **data = read_kinetisense("../../../data/Craig_Walking_tredmil.csv");

  for (int k = 0; k < 20; k++)
     delete[] data[k];

  return 0;
}
