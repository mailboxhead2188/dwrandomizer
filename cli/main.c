
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dwr.h"
#include "dwr_types.h"
#include "map.h"
#include "sprites.h"


static void print_usage(const char *command, char *default_flags)
{
    size_t i;

    printf("Usage %s <rom_file> [flags [seed [sprite]]] [output stats dir] <output_dir>\n", command);
    printf("\n");
    printf("A randomizer for Dragon Warrior for NES\n");
    printf("\n");
    printf("Flags:\n");
    printf("    C  Random chest and searchable item contents.\n");
    printf("    D  Enable Death Necklace functionality (+10 ATK -25%% HP)\n");
    printf("    F  Set XP requirements for each level to 75%% of normal.\n");
    printf("    G  Enable randomization of player stat growth.\n");
    printf("    H  Apply game speed hacks\n");
    printf("    K  Shuffle the game music.\n");
    printf("    M  Randomize the level spells are learned.\n");
    printf("    R  Enable menu wrap-around\n");
    printf("    P  Enable randomization of monster attack patterns.\n");
    printf("    Q  Disables the game music.\n");
    printf("    V  Set XP requirements for each level to 50%% of normal.\n");
    printf("    W  Random weapon shops.\n");
    printf("    Z  Random monster zones.\n");

    printf("    b  Big Swamp - make a larger portion of the terrain swamp\n");
    printf("    c  Cursed princess mode\n");
    printf("    d  Random monster drops (XP and gold)\n");
    printf("    e  Random monster stats\n");
    printf("    k  Don't require keys to open doors\n");
    printf("    l  Metal Slimes always have a chance to run\n");
    printf("    m  Modern spell names\n");
    printf("    o  Open Charlock. No Rainbow Drop required.\n");
    printf("    s  Shortened Charlock\n");
    printf("    t  Enable faster text\n");
    printf("    v  Vanilla (Original) Map\n");
    printf("    w  Random weapon prices\n");

    printf("\n");
    printf("If flags are not specified, the flags \"%s\" will be used\n",
            default_flags);
    printf("If the seed is not specified, a random seed will be chosen\n");
    printf("\n");
    printf("Sprite should be one of: ");
    for(i=0; i < sprite_count(); i++) {
        if (i) {
            printf(", %s", dwr_sprite_names[i]);
        } else {
            printf("%s", dwr_sprite_names[i]);
        }
    }
    printf("The output stats directory contains files pertaining to the finalized stats of all the randomized items and locations");
    printf("\n");
}

int main(int argc, char **argv)
{
    uint64_t seed;
    const char *sprite;
    char *flags;
    char default_flags[] = DEFAULT_FLAGS;
    char *input_file, *output_dir, *output_stats_dir;

    printf("DWRandomizer version %s\n", VERSION);
    if (argc < 3) {
        print_usage(argv[0], default_flags);
        exit(0);
    }

    input_file = argv[1];
    output_dir = argv[argc-1];

    if (argc >= 4) {
        output_stats_dir = argv[argc-2];
    }
    else
    {
        output_stats_dir = NULL;
    }
    
    if (argc >= 5) {
        flags = argv[2];
    } else {
        flags = default_flags;
    }
    if (argc < 6 || sscanf(argv[3], "%"PRIu64, &seed) != 1) {
        srand(time(NULL));
        seed = ((uint64_t)rand() << 32) | ((uint64_t)rand() & 0xffffffffL);
    }
    if (argc > 6) {
        sprite = argv[4];
    } else {
        sprite = "Random";
    }

    printf("Randomizing using seed: %"PRIu64" with flags %s\n", seed, flags);

    dwr_randomize(input_file, seed, flags, sprite, output_dir, output_stats_dir);

    return 0;
}

