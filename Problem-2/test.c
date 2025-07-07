#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "buffer_builder.c"

struct stream { int dummy; };

FILE *log_file = NULL;
int stream_index = 0;

uint8_t *mock_data[] = {
    (uint8_t *)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx",  // 50 bytes
    (uint8_t *)"ABCDEFGHIJKLMNOPQRST",                              // 20 bytes
    NULL
};

struct fixed_buff* fixed_buff_alloc(void) {
    return (struct fixed_buff *)calloc(1, sizeof(struct fixed_buff));
}

uint8_t* stream_get(struct stream *s, unsigned int *data_len) {
    if (mock_data[stream_index] == NULL) return NULL;

    *data_len = strlen((char *)mock_data[stream_index]);
    uint8_t *copy = malloc(*data_len);
    memcpy(copy, mock_data[stream_index], *data_len);
    stream_index++;
    return copy;
}

void print_list(struct fixed_buff *head) {
    int count = 1;
    while (head) {
        fprintf(log_file, "Buffer %d: data_len = %u, data = \"", count, head->data_len);
        printf("Buffer %d: data_len = %u, data = \"", count, head->data_len);
        for (unsigned int i = 0; i < head->data_len; ++i) {
            fprintf(log_file, "%c", head->data[i]);
            printf("%c", head->data[i]);
        }
        fprintf(log_file, "\"\n");
        printf("\"\n");
        head = head->next;
        count++;
    }
    fprintf(log_file, "SUCCESS: Data copied to fixed_buff list\n");
    printf("SUCCESS: Data copied to fixed_buff list\n\n\n");
}

int main() {
    log_file = fopen("output.log", "a");
    if (!log_file) {
        printf("ERROR: Could not open output.log\n");
        return 1;
    }

    struct stream s;
    struct fixed_buff *list = build_fixed_buff_list(&s);

    fprintf(log_file, "--- Fixed Buffer Output ---\n");
    printf("\n--- Fixed Buffer Output ---\n");
    print_list(list);

    fclose(log_file);
    return 0;
}
