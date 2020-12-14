#include <zlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// http://www.iana.org/assignments/media-types/application/zip

uint32_t get_signature(FILE * fp);

#define LOCAL_FILE_HEADER_SIGNATURE                 0x04034b50
#define CENTRL_DIRECTORY_FILE_HEADER_SIGNATURE      0x02014b50
#define END_CENTRL_DIRECTORY_FILE_HEADER_SIGNATURE  0x06054b50

typedef struct __zip_local_file_header {
    uint32_t signature;
    uint16_t version;
    uint16_t flags;
    uint16_t method;
    uint16_t time;
    uint16_t date;
    struct {
        uint32_t crc32;
        uint32_t compressed;
        uint32_t uncompressed;
    } __attribute__((aligned(1), packed)) data;
    uint16_t filename;
    uint16_t extra;
} __attribute__((aligned(1), packed)) zip_local_file_header;

typedef struct __local_file {
    zip_local_file_header header;
    char * filename;
    unsigned char * extra;
    long offset;
} local_file;


local_file * get_local_file(local_file * o, FILE * fp);
local_file * free_local_file(local_file * o);

typedef struct __zip_central_file_header {
    uint32_t signature;
    uint16_t made;
    uint16_t version;
    uint16_t flags;
    uint16_t method;
    uint16_t time;
    uint16_t date;
    struct {
        uint32_t crc32;
        uint32_t compressed;
        uint32_t uncompressed;
    } __attribute__((aligned(1), packed)) data;
    uint16_t filename;
    uint16_t extra;
    uint16_t comment;
    uint16_t disk;
    uint16_t internal;
    uint32_t external;
    uint32_t relative;
} __attribute__((aligned(1), packed)) zip_central_file_header;

typedef struct __central {
    zip_central_file_header header;
    char * filename;
    unsigned char * extra;
    char * comment;
} central;

central * free_central(central * o);
central * get_central(central * o, FILE * fp);

typedef struct __zip_end_central_header {
    uint32_t signature;
    uint16_t disk;
    uint16_t start;
    uint16_t tracks;
    uint16_t directories;
    uint32_t size;
    uint32_t offset;
    uint16_t comment;
} __attribute__((aligned(1), packed)) zip_end_central_header;

typedef struct __end_central {
    zip_end_central_header header;
    char * comment;
} end_central;

end_central * get_end_central(end_central * o, FILE * fp);
end_central * free_end_central(end_central * o);

// 	end of central dir signature    4 bytes  (0x06054b50)
// 	number of this disk             2 bytes
// 	number of the disk with the start of the central directory  2 bytes
// 	total number of entries in the central dir on this disk    2 bytes
// 	total number of entries in the central dir                 2 bytes
// 	size of the central directory   4 bytes
// 	offset of start of central directory with respect to the starting disk number        4 bytes
// 	zipfile comment length          2 bytes
// 	zipfile comment (variable size)

int main()
{
    FILE * source = fopen("doom.zip", "rb");
    if(source) {
        while(1) {
            uint32_t signature = get_signature(source);
            if(signature == LOCAL_FILE_HEADER_SIGNATURE) {
                local_file * f = get_local_file(NULL, source);
                if(f){
                    printf("local: %s\n", f->filename);
                    free_local_file(f);
                    continue;
                }
            } else if(signature == CENTRL_DIRECTORY_FILE_HEADER_SIGNATURE) {
                central * f = get_central(NULL, source);
                if(f){
                    printf("central: %s\n", f->filename);
                    free_central(f);
                    continue;
                }
            } else if(signature == END_CENTRL_DIRECTORY_FILE_HEADER_SIGNATURE) {
                end_central * f = get_end_central(NULL, source);
                if(f) {
                    if(strlen(f->comment) > 0) {
                        printf("%s\n", f->comment);
                    }
                    printf("success\n");
                }
                break;
            }
            printf("%08x\n", signature);
            break;
        }

        fclose(source);
    }
    
    return 0;
}

uint32_t get_signature(FILE * fp)
{
    uint32_t signature = 0;
    if(fread(&signature, 1, sizeof(uint32_t), fp) != sizeof(uint32_t)) {
        printf("fail to read\n");
        return 0;
    }
    fseek(fp, -4, SEEK_CUR);
    return signature;
}

local_file * get_local_file(local_file * o, FILE * fp)
{
    if(o == NULL) {
        o = (local_file *) malloc(sizeof(local_file));
        memset(o, 0, sizeof(local_file));
        if(o == NULL) {
            printf("fail to malloc(...)\n");
            return NULL;
        }
    }
    o->offset = ftell(fp);

    if(fread(&o->header, 1, sizeof(zip_local_file_header), fp) == sizeof(zip_local_file_header)) {
        // printf("signature: %d\n", o->header.signature);
        // printf("version: %d\n", o->header.version);
        // printf("flags: %x\n", o->header.flags);
        // printf("method: %d\n", o->header.method);
        // printf("time: %d\n", o->header.time);
        // printf("date: %d\n", o->header.date);
        // printf("crc32: %d\n", o->header.crc32);
        // printf("compressed: %d\n", o->header.compressed);
        // printf("uncompressed: %d\n", o->header.uncompressed);
        // printf("filename: %d\n", o->header.filename);
        // printf("extra: %d\n", o->header.extra);
        if(o->filename) {
            free(o->filename);
        }
        o->filename = malloc(o->header.filename + 1);
        if(fread(o->filename, 1, o->header.filename, fp) != o->header.filename) {
            free(o->filename);
            fclose(fp);
            return NULL;
        }
        o->filename[o->header.filename] = 0;
        if(o->extra) {
            free(o->extra);
        }
        o->extra = malloc(o->header.extra);
        if(fread(o->extra, 1, o->header.extra, fp) != o->header.extra) {
            free(o->extra);
            fclose(fp);
            return NULL;
        }
        if(o->header.flags & 0x08) {
            printf("check this\n");
        }
        fseek(fp, o->header.data.compressed, SEEK_CUR);
    }
    return o;
}

local_file * free_local_file(local_file * o)
{
    if(o){
        free(o->extra);
        free(o->filename);
        free(o);
    }
    return NULL;
}

central * get_central(central * o, FILE * fp) {
    if(o == NULL) {
        o = (central *) malloc(sizeof(central));
        memset(o, 0, sizeof(central));
        if(o == NULL) {
            printf("fail to malloc(...)\n");
            return NULL;
        }
    }

    if(fread(&o->header, 1, sizeof(zip_central_file_header), fp) == sizeof(zip_central_file_header)) {
        if(o->filename) {
            free(o->filename);
        }
        o->filename = malloc(o->header.filename + 1);
        if(fread(o->filename, 1, o->header.filename, fp) != o->header.filename) {
            free(o->filename);
            fclose(fp);
            return NULL;
        }
        o->filename[o->header.filename] = 0;
        if(o->extra) {
            free(o->extra);
        }
        o->extra = malloc(o->header.extra);
        if(fread(o->extra, 1, o->header.extra, fp) != o->header.extra) {
            free(o->extra);
            fclose(fp);
            return NULL;
        }
        if(o->comment) {
            free(o->comment);
        }
        o->comment = malloc(o->header.comment + 1);
        if(fread(o->comment, 1, o->header.comment, fp) != o->header.comment) {
            free(o->comment);
            fclose(fp);
            return NULL;
        }
        o->comment[o->header.comment] = 0;
        if(o->header.flags & 0x08) {
            printf("check this\n");
        }
    }
    return o;
}

central * free_central(central * o)
{
    if(o) {
        free(o->filename);
        free(o->extra);
        free(o->comment);
        free(o);
    }
    return NULL;
}

end_central * get_end_central(end_central * o, FILE * fp)
{
    if(o == NULL) {
        o = (end_central *) malloc(sizeof(end_central));
        memset(o, 0, sizeof(end_central));
        if(o == NULL) {
            printf("fail to malloc(...)\n");
            return NULL;
        }
    }

    if(fread(&o->header, 1, sizeof(zip_end_central_header), fp) == sizeof(zip_end_central_header)) {
        if(o->comment) {
            free(o->comment);
        }
        o->comment = malloc(o->header.comment + 1);
        if(fread(o->comment, 1, o->header.comment, fp) != o->header.comment) {
            free(o->comment);
            fclose(fp);
            return NULL;
        }
        o->comment[o->header.comment] = 0;
    }
    return o;
}

/**
 * FREE END CENTRAL HEADER
 */
end_central * free_end_central(end_central * o)
{
    if(o) {
        free(o->comment);
        free(o);
    }
    return NULL;
}