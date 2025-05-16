#include "database.h"

void saveWordDatabase(WordDatabase* db) {
    FILE* file = fopen(WORDS_FILE, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "%d\n", db->count);
    
    for (int i = 0; i < db->count; i++) {
        fprintf(file, "%s\n%s\n", db->words[i], db->hints[i]);
    }
    
    fclose(file);
    printf("Word database saved successfully!\n");
}

bool loadWordDatabase(WordDatabase* db) {
    FILE* file = fopen(WORDS_FILE, "r");
    // if (file == NULL) {
    //     initializeDefaultWordDatabase(db);
    //     saveWordDatabase(db);
    //     return false;
    // }

    if (fscanf(file, "%d\n", &db->count) != 1) {
        fclose(file);
        return false;
    }

    for (int i = 0; i < db->count; i++) {
        if (fgets(db->words[i], MAX_WORD_LENGTH, file) == NULL) {
            fclose(file);
            return false;
        }
        db->words[i][strcspn(db->words[i], "\n")] = 0;
        
        if (fgets(db->hints[i], MAX_HINT_LENGTH, file) == NULL) {
            fclose(file);
            return false;
        }
        db->hints[i][strcspn(db->hints[i], "\n")] = 0;
    }
    
    fclose(file);
    printf("Word database loaded successfully!\n");
    return true;
}

// void initializeDefaultWordDatabase(WordDatabase* db) {
//     db->count = 100;
    
//     char initialWords[][MAX_WORD_LENGTH] = {
//         "apple", "banana", "cherry", "dog", "elephant",
//         "flower", "guitar", "happy", "icecream", "jungle",
//         "kangaroo", "lemon", "mountain", "notebook", "orange",
//         "penguin", "quasar", "rainbow", "sunflower", "turtle",
//         "umbrella", "violin", "watermelon", "xylophone", "zebra",
//         "astronomy", "butterfly", "caterpillar", "dolphin", "earth",
//         "fireworks", "galaxy", "happiness", "island", "jigsaw",
//         "kite", "lighthouse", "moonlight", "novel", "ocean",
//         "paradise", "quilt", "rocket", "starlight", "telescope",
//         "universe", "volcano", "whale", "xray", "yellow",
//         "zoo", "breeze", "carousel", "dandelion", "effervescent",
//         "fountain", "gentle", "harmony", "illusion", "journey",
//         "kaleidoscope", "lullaby", "marvel", "nostalgia", "overture",
//         "paradox", "quintessence", "serendipity", "tranquil", "unique",
//         "vivid", "whimsical", "xanadu", "yearning", "zenith",
//         "ballet", "comet", "delight", "ethereal", "fantasy",
//         "graceful", "hologram", "innocence", "jubilation", "kismet",
//         "labyrinth", "mystical", "nebula", "opulent", "perennial",
//         "quicksilver", "resplendent", "serenity", "twilight", "utopia",
//         "velvet", "wonder", "xenon", "yearn", "zephyr"
//     };

//     char initialHints[][MAX_HINT_LENGTH] = {
//         "A common fruit with a red or green skin.",
//         "A yellow fruit that is peeled before eating.",
//         "A small, round fruit with a pit inside.",
//         "A domesticated, loyal animal often kept as a pet.",
//         "A large mammal known for its long trunk and tusks.",
//         "A colorful and fragrant bloom.",
//         "A musical instrument with strings.",
//         "An emotion characterized by joy and contentment.",
//         "A frozen dessert often enjoyed on a hot day.",
//         "A dense and overgrown forest.",
//         "A marsupial native to Australia.",
//         "A citrus fruit with a sour taste.",
//         "A towering landform with rocky peaks.",
//         "A notebook for writing and recording information.",
//         "A citrus fruit with a sweet and tangy flavor.",
//         "A flightless bird with distinctive black and white feathers.",
//         "A celestial object emitting powerful energy.",
//         "A spectrum of colors in the sky after rain.",
//         "A bright and cheerful flower.",
//         "A reptile with a hard shell.",
//         "A device to protect from rain.",
//         "A string instrument played with a bow.",
//         "A large, juicy fruit with green rind and red flesh.",
//         "A percussion instrument with wooden bars.",
//         "A black and white striped mammal.",
//         "The scientific study of celestial objects and phenomena.",
//         "An insect with colorful wings.",
//         "The larval stage of a butterfly.",
//         "A marine mammal known for its intelligence.",
//         "The third planet from the sun.",
//         "Explosive and colorful pyrotechnic displays.",
//         "A vast system of stars, gas, and dust.",
//         "A state of well-being and contentment.",
//         "A landmass surrounded by water.",
//         "A puzzle with irregularly shaped pieces.",
//         "A flying toy tethered to a string.",
//         "A tall structure with a light to guide ships.",
//         "Soft, natural light from the moon.",
//         "A long fictional prose narrative.",
//         "A large body of saltwater.",
//         "A place of perfect happiness and bliss.",
//         "A bed cover made of stitched fabric.",
//         "A vehicle that travels into space.",
//         "Light from stars at night.",
//         "An optical instrument for viewing distant objects.",
//         "All that exists, including stars, galaxies, and space.",
//         "A mountain that spews lava and ash.",
//         "A large marine mammal.",
//         "A form of electromagnetic radiation.",
//         "The color of ripe lemons.",
//         "A place where animals are kept for public exhibition.",
//         "A gentle wind.",
//         "A rotating machine with seats for amusement.",
//         "A wildflower with fluffy seed heads.",
//         "Bubbly, fizzy, and sparkling.",
//         "A stream of water usually shot upward.",
//         "Soft and mild, not harsh.",
//         "A state of peaceful coexistence.",
//         "Something that deceives the senses.",
//         "A journey or trip.",
//         "A constantly changing pattern or sequence.",
//         "A soothing song to help sleep.",
//         "Something causing wonder or astonishment.",
//         "A feeling of pleasure mixed with sadness.",
//         "An introductory musical composition.",
//         "A statement or situation that contradicts itself.",
//         "The most perfect or typical example of something.",
//         "An unexpected and fortunate discovery.",
//         "Calm and peaceful.",
//         "Being the only one of its kind.",
//         "Clear, detailed, and bright.",
//         "Playfully quaint or fanciful.",
//         "An idealized place of great beauty and contentment.",
//         "A yearning for something.",
//         "The highest point in the heavens.",
//         "A form of dance.",
//         "A celestial object with a bright tail of gas and dust.",
//         "A great source of joy and delight.",
//         "Extremely delicate and light in a way that seems not to be of this world.",
//         "An imagined world or sequence of events.",
//         "Graceful and elegant in form or movement.",
//         "A three-dimensional image created by laser beams.",
//         "The state of being free from guilt or sin.",
//         "A feeling of great happiness and triumph.",
//         "Destiny or fate.",
//         "A winding and confusing network.",
//         "Having a spiritual significance or symbolism.",
//         "A luminous patch of gas or dust in the night sky.",
//         "Richly and impressively splendid.",
//         "Lasting through the years.",
//         "A flowing, shining metal.",
//         "Brilliant and magnificent.",
//         "The state of being calm and peaceful.",
//         "The soft, diffused light from the sky when the sun is below the horizon.",
//         "An imagined perfect place or state of things.",
//         "A soft fabric with a smooth and dense pile.",
//         "A feeling of amazement and admiration.",
//         "A chemical element often used in lights.",
//         "To have an intense desire or longing for something.",
//         "A gentle, mild wind."
//     };

//     for (int i = 0; i < db->count; i++) {
//         strcpy(db->words[i], initialWords[i]);
//         strcpy(db->hints[i], initialHints[i]);
//     }
// }

void addWordToDatabase(WordDatabase* db, const char* word, const char* hint) {
    if (db->count < MAX_WORDS) {
        strcpy(db->words[db->count], word);
        strcpy(db->hints[db->count], hint);
        db->count++;
        printf("Word and hint added successfully!\n");
        saveWordDatabase(db);
    } else {
        printf("Database is full. Cannot add more words.\n");
    }
}

void addNewWord(WordDatabase* db) {
    system("cls");
    char word[MAX_WORD_LENGTH];
    char hint[MAX_HINT_LENGTH];

    printf("\nEnter the new word (lowercase, max %d characters): ", MAX_WORD_LENGTH-1);
    scanf("%s", word);
    
    printf("Enter the hint for '%s' (max %d characters): ", word, MAX_HINT_LENGTH-1);
    getchar(); // Consume newline
    fgets(hint, MAX_HINT_LENGTH, stdin);
    hint[strcspn(hint, "\n")] = 0; // Remove newline
    
    addWordToDatabase(db, word, hint);
}