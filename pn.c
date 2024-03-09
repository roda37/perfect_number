// perfect numbers finder
// https://github.com/roda37/perfect_number

#include <stdio.h>
#include <gmp.h>
#include <math.h>

void save(mpz_t num) {
    char buffer[100000];
    mpz_get_str(buffer, 10, num); // Convert num to a string
    FILE *file = fopen("the_list", "a");
    fprintf(file, "%s\n", buffer);
    fclose(file);
}

int prime(mpz_t n) {
    mpz_t i, sqrt_n;
    mpz_init(i);
    mpz_init(sqrt_n);

    if (mpz_cmp_ui(n, 1) <= 0) {
        mpz_clear(i);
        mpz_clear(sqrt_n);
        return 0;
    }

    mpz_sqrt(sqrt_n, n);
    for (mpz_set_ui(i, 2); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 1)) {
        if (mpz_divisible_p(n, i) != 0) {
            mpz_clear(i);
            mpz_clear(sqrt_n);
            return 0;
        }
    }

    mpz_clear(i);
    mpz_clear(sqrt_n);
    return 1;
}

int main() {
	// lead uint
    mpz_t num;
    mpz_init_set_ui(num, 1);

	// sum
	mpz_t sum;
    mpz_init_set_ui(sum, 1);

    while (1) {
		// multiply num, add to sum
        mpz_mul_ui(num, num, 2);
		mpz_add(sum, sum, num);

		// if prime(sum) == true mul it with num, print perfect number
		if (prime(sum)) {
			mpz_t burn;
			mpz_init(burn);
			mpz_mul(burn, sum, num);

			//mpz_out_str(stdout, 10, burn);
			//putchar('\n');
			save(burn);

			mpz_clear(burn);
		}
    }
    
    mpz_clear(num);
    return 0;
}
