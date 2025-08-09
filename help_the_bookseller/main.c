#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Summary {
    char letter;
    unsigned int quantity;
};

char* stockSummary(
    const char* const books[], size_t n_books,
    const char* const categories[], size_t n_categories
);
unsigned int get_amount(const char* stock);
char* format_summary(const struct Summary* summaries, size_t n_categories);

int main() {
    printf("Hello C!\n");

	const char* art[5] = {"ROXANNE 102", "RHODODE 123", "BKWRKAA 125", "BTSQZFG 239", "DRTYMKH 060"};
	const char* cd[4] = {"B", "R", "D", "X"};

    char* result = stockSummary(art, 5, cd, 4);
    printf("%s\n", result);
    
    free(result);
    return 0;
}

char* stockSummary(
    const char* const books[/* n_books */], size_t n_books,
	const char* const categories[/* n_categories */], size_t n_categories
) {
    if (!books || n_books == 0 || n_categories == 0) return calloc(1, 1);
    
    struct Summary summaries[n_categories];
 
    for (size_t i = 0; i < n_categories; i++) {
        summaries[i].letter = categories[i][0];
        summaries[i].quantity = 0;
    }
 
    for (size_t i = 0; i < n_books; i++) {
        unsigned int num = get_amount(books[i]);
        
        for (size_t k = 0; k < n_categories; k++) {
            if (books[i][0] == summaries[k].letter) {
                summaries[k].quantity = summaries[k].quantity + num;
            }
        }
    }
    
    char* result = format_summary(summaries, n_categories);
    return result;
}

char* format_summary(const struct Summary* summaries, size_t n_categories) {
    size_t buffer_size = n_categories * 20 + 1;
    char* result = malloc(buffer_size);
    if (!result) return NULL;

    size_t pos = 0;

    for (size_t i = 0; i < n_categories; i++) {
        // Write the separator only after the first element
        if (i > 0) {
            int written = snprintf(result + pos, buffer_size - pos, " - ");
            if (written < 0 || (size_t)written >= buffer_size - pos) break;  // Buffer full
            pos += written;
        }

        int written = snprintf(
            result + pos, buffer_size - pos, "(%c : %u)",
            summaries[i].letter, summaries[i].quantity
        );
        if (written < 0 || (size_t)written >= buffer_size - pos) break;  // Buffer full
        pos += written;
    }

    return result;
}

unsigned int get_amount(const char* stock) {
    unsigned int value = 0;

    for (size_t i = 0; stock[i] != '\0'; i++) {
        if (stock[i] >= '0' && stock[i] <= '9') {
            value = value * 10 + (stock[i] - '0');
        }
    }
    
    return value;
}