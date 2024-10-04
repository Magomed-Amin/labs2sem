#include <stdlib.h>
#include <stdio.h>
#include "computer.h"
#include "tools.h"

Computer *input_computer(void) {
    Computer *comp = (Computer*)malloc(sizeof(Computer));
    printf("Enter student name: ");
    scanf("%s", comp->name);

    printf("Enter number of processors: ");
    scanf("%d", &comp->number_of_processors);

    printf("Enter type of processors: ");
    scanf("%s", comp->type_of_processors);

    printf("Enter memory capacity: ");
    scanf("%d", &comp->memory_capacity);

    printf("Enter type of video-controller (1 - Builtin, 2 - External, 3 - AGP, 4 - PCI): ");
    int n;
    scanf("%d", &n);
    comp->video_controller = (vc)n;

    printf("Enter video memory capacity: ");
    scanf("%d", &comp->video_memory_capacity);

    printf("Enter video memory type (1 - SCSI/IDE, 2 - ATA/SATA): ");
    scanf("%d", &n);
    comp->video_memory_type = (vmt)n;

    printf("Enter number of hard drives: ");
    scanf("%d", &comp->number_of_hard_drives);

    printf("Enter capacity of hard drives: ");
    scanf("%d", &comp->capacity_of_hard_drives);

    printf("Enter number of integrated controllers: ");
    scanf("%d", &comp->number_of_integrated_controllers);

    printf("Enter number of external devices: ");
    scanf("%d", &comp->number_of_processors);

    printf("Enter operation system: ");
    scanf("%s", comp->os);

    char temp[5];
    printf("Accessories are branded (enter true/false): ");
    scanf("%s", temp);
    comp->is_branded = Branded(temp);

    return comp;
}