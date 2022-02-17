#include <stdio.h>

// Normal struct definition
struct amino_acid {
  char type;
  int charge;
  double position[3];
  double velocity[3];
};

// Now 'struct amino_acid' is just 'amino_acid_t'
typedef struct amino_acid amino_acid_t;

// Direct type definition
typedef struct {
  char type;
  int charge;
  double position[3];
  double velocity[3];
} amino_acid_type_def;

int main(int argc, char const *argv[]) {
  // Three different types of declaring a struct or typedef struct
  struct amino_acid sizes;
  amino_acid_t sizes_t;
  amino_acid_type_def sizes_td_t;

  printf("Struct: %ld\nAmino Acid (Char): %ld\nCharge (Int): %ld\nPosition "
         "(array(double)): %ld\nVelocity (array(double)): %ld\n\n",
         sizeof(sizes), sizeof(sizes.type), sizeof(sizes.charge),
         sizeof(sizes.position), sizeof(sizes.velocity));

  printf(
      "Struct then Typedef: %ld\nAmino Acid (Char): %ld\nCharge (Int): "
      "%ld\nPosition (array(double)): %ld\nVelocity (array(double)): %ld\n\n",
      sizeof(sizes_t), sizeof(sizes_t.type), sizeof(sizes_t.charge),
      sizeof(sizes_t.position), sizeof(sizes_t.velocity));

  printf(
      "Typedef Struct: %ld\nAmino Acid (Char): %ld\nCharge (Int): "
      "%ld\nPosition (array(double)): %ld\nVelocity (array(double)): %ld\n\n",
      sizeof(sizes_td_t), sizeof(sizes_td_t.type), sizeof(sizes_td_t.charge),
      sizeof(sizes_td_t.position), sizeof(sizes_td_t.velocity));

  printf("Overall Sum: %ld\n", sizeof(sizes.type) + sizeof(sizes.charge) +
                                   sizeof(sizes.position) +
                                   sizeof(sizes.velocity));
  return 0;
}
