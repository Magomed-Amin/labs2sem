#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "computer.h"
#include "tools.h"

char *VC(vc type) {
    char *types[] = {"Builtin", "External", "AGP", "PCI", "incorrect type"};
    return types[(int)type];
}

char *VMT(vmt type) {
    char *types[] = {"SCSI/IDE", "ATA/SATA", "incorrect type"};
    return types[(int)type];
}

vmt Vmt(const char type[20]) {
    if (!(strcmp(type, "SCSI/IDE"))) return SCSI_IDE;
    if (!(strcmp(type, "ATA/SATA"))) return ATA_SATA;
    return vmt_error;
}

vc Vc(const char type[20]) {
    if (!(strcmp(type, "Builtin"))) return Builtin;
    if (!(strcmp(type, "External"))) return External;
    if (!(strcmp(type, "AGP"))) return AGP;
    if (!(strcmp(type, "PCI"))) return PCI;
    return vc_error;
}

char *branded(bool value) {
    if (value == true)
        return "true";
    return "false";
}

bool Branded(char value[5]) {
    if (!strcmp(value, "true"))
        return true;
    return false;
}

void write_computer(FILE *fileToRead, FILE *fileToWrite) {
    Computer p;
    char t1[20], t2[20];
    char t3[20];
    while (fscanf(
            fileToRead, "%s %d %s %d %s %d %s %d %d %d %d %s %s", p.name, &p.number_of_processors,
            p.type_of_processors, &p.memory_capacity, t2, &p.video_memory_capacity, t1, &p.number_of_hard_drives,
            &p.capacity_of_hard_drives, &p.number_of_integrated_controllers, &p.number_of_external_devices, p.os, t3
    ) == 13 ) {
        p.video_memory_type = Vmt(t1);
        p.video_controller = Vc(t2);
        p.is_branded = Branded(t3);
        fwrite(&p, sizeof p, 1, fileToWrite);
    }

    fclose(fileToRead);
    fclose(fileToWrite);
}

void write_random_computer(FILE *fileToWrite, int count) {
    srand(time(NULL));
    char *names[] = {" misha", " vasya", "  gena", " gosha", "kostya", "  dima", "  ivan", " zhora"};
    char *procs[] = {"  IBM", "  AMD", "Intel"};
    char *os[] = {"Windows", "  Linux", "  macOS"};
    vc vc_types[4] = {Builtin, External, AGP, PCI};
    vmt vmt_types[2] = {SCSI_IDE, ATA_SATA};
    bool brand[2] = {true, false};

    for (int i = 0; i < count; i++) {
        Computer comp;
        int temp = rand() % 8;
        for (int j = 0; j < 6; j++) {
            comp.name[j] = names[temp][j];
        }
        comp.number_of_processors = rand() % 10;
        temp = rand() % 3;
        for (int j = 0; j < 5; j++) {
            comp.type_of_processors[j] = procs[temp][j];
        }
        comp.memory_capacity = rand() % 1000;
        comp.video_controller = vc_types[rand() % 4];
        comp.video_memory_capacity = rand() % 1000;
        comp.video_memory_type = vmt_types[rand() % 2];
        comp.number_of_hard_drives = rand() % 10;
        comp.capacity_of_hard_drives = rand() % 1000;
        comp.number_of_integrated_controllers = rand() % 10;
        comp.number_of_external_devices = rand() % 100;
        temp = rand() % 3;
        for (int j = 0; j < 7; j++) {
            comp.os[j] = os[temp][j];
        }
        comp.is_branded = brand[rand() % 2];
        fwrite(&comp, sizeof comp, 1, fileToWrite);

    }


}

void printPerson(Computer *p) {
    printf("= %9s = %13d = %11s = %16d = %14s = %15d = %15s = %18d = %18d = %23d = %18d = %10s = %10s =\n",
           p->name, p->number_of_processors, p->type_of_processors, p->memory_capacity, VC(p->video_controller),
           p->video_memory_capacity, VMT(p->video_memory_type), p->number_of_hard_drives,
           p->capacity_of_hard_drives, p->number_of_integrated_controllers, p->number_of_external_devices, p->os,
           branded(p->is_branded));
}

void save_input_computer(char db[20]) {
    Computer *comp = input_computer();
    FILE *temp = fopen("temp.txt", "w");
    FILE *dtb = fopen(db, "a+");
    fprintf(
            temp,
            "%s %d %s %d %s %d %s %d %d %d %d %s %s",
            comp->name,
            comp->number_of_processors,
            comp->type_of_processors,
            comp->memory_capacity,
            VC(comp->video_controller),
            comp->video_memory_capacity,
            VMT(comp->video_memory_type),
            comp->number_of_hard_drives,
            comp->capacity_of_hard_drives,
            comp->number_of_integrated_controllers,
            comp->number_of_external_devices,
            comp->os,
            branded(comp->is_branded)
    );
    fclose(temp);
    temp = fopen("temp.txt", "r");
    write_computer(temp, dtb);
    remove("temp.txt");
}

void usage(void) {
    printf("Usage: [keys]\nKeys:\n");
    printf("\t-g - generate default database\n");
    printf("\t-f - print all entries in database\n");
    printf("\t-i - add entry to database from stdin\n");
    printf("\t-p - show computers with branded accessories\n");
    printf("\t-d - clear database\n");
}

void printFile(FILE *file, char divider[230], bool select) {
    printf("%s\n", divider);
    printf("%s\n", HEADER);
    printf("%s\n", divider);
    Computer computer;
    while (fread(&computer, sizeof(Computer), 1, file) == 1) {
        if (computer.is_branded || !select) {
            printPerson(&computer);
            printf("%s\n", divider);
        }
    }
    fclose(file);
}
