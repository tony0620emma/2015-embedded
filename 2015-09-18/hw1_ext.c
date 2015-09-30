#include <immintrin.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

struct timespec timespec;

double compute_pi_base(size_t dt)
{
	double pi = 0.0;
	double delta = 1.0 / dt;
	for (size_t i = 0; i < dt; i++) {
		double x = (double) i / dt;
		pi +=delta / (1.0 + x * x);
	}

	return pi * 4.0;
}

double compute_pi_avxsimd(size_t dt)
{

	double pi = 0.0;
	double delta = 1.0 / dt;
	register __m256d ymm0, ymm1, ymm2, ymm3, ymm4;
	ymm0 = _mm256_set1_pd(1.0);
	ymm1 = _mm256_set1_pd(delta);
	ymm2 = _mm256_set_pd(delta * 3, delta * 2, delta * 1, 0.0);
	ymm4 = _mm256_setzero_pd();

	for (int i = 0; i <= dt - 4; i += 4) {
		ymm3 = _mm256_set1_pd(i * delta);
		ymm3 = _mm256_add_pd(ymm3, ymm2);
		ymm3 = _mm256_mul_pd(ymm3, ymm3);
		ymm3 = _mm256_add_pd(ymm0, ymm3);
		ymm3 = _mm256_div_pd(ymm1, ymm3);
		ymm4 = _mm256_add_pd(ymm4, ymm3);
	}
	double tmp[4] __attribute__((aligned(32)));
	_mm256_store_pd(tmp, ymm4);
	pi += tmp[0] + tmp[1] + tmp[2] + tmp[3];

	return pi * 4.0;
}

double compute_pi_avxsimd_v2(size_t dt)
{

	double pi = 0.0;
	double delta = 1.0 / dt;
	register __m256d ymm0, ymm1, ymm2, ymm3, ymm4;
	ymm0 = _mm256_set1_pd(1.0);
	ymm1 = _mm256_set1_pd(delta);
	ymm2 = _mm256_set_pd(delta * 3, delta * 2, delta * 1, 0.0);
	ymm4 = _mm256_setzero_pd();

	for (int i = 0; i <= dt - 4; i += 4) {
		ymm3 = _mm256_set1_pd(i * delta);
		ymm3 = _mm256_add_pd(ymm3, ymm2);
		ymm3 = _mm256_fmadd_pd(ymm3, ymm3, ymm0);
		ymm3 = _mm256_div_pd(ymm1, ymm3);
		ymm4 = _mm256_add_pd(ymm4, ymm3);
	}
	double tmp[4] __attribute__((aligned(32)));
	_mm256_store_pd(tmp, ymm4);
	pi += tmp[0] + tmp[1] + tmp[2] + tmp[3];

	return pi * 4.0;
}

int main(int argc, char *argv[])
{
	clock_gettime(CLOCK_MONOTONIC, &timespec);
	double start_time = timespec.tv_sec + 
	       		((double)(timespec.tv_nsec / 10000)) / 100000;	
	size_t i;
	for (i = 0; i < 3; i++) {
#if defined(AVXSIMD)
		compute_pi_avxsimd(128000000);
#elif defined(AVXSIMD2)
		printf("pi = %lf\n", compute_pi_avxsimd_v2(128000000));
#elif defined(BASE)
		compute_pi_base(128000000);
#endif
	}
	clock_gettime(CLOCK_MONOTONIC, &timespec);
	double end_time = timespec.tv_sec + 
	       		((double)(timespec.tv_nsec / 10000)) / 100000;
#if defined(AVXSIMD)
		printf("\n\nAVXSIMD version 1\n");
#elif defined(AVXSIMD2)
		printf("\n\nAVXSIMD version 2\n");
#elif defined(BASE)
		printf("\n\nBASE version\n");
#endif
	printf("total time elapsed : %lfs\n", end_time - start_time);

	return 0;
}
