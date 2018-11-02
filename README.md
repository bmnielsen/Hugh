# Hugh
AI for StarCraft: Brood War

## About
Hugh is the little brother of [Locutus](https://github.com/bmnielsen/Locutus). Hugh was created for the [AI TinyCraft Tournament](https://sites.google.com/view/mcrave/aitt), so called as participating bots consist of a single C++ header file not exceeding 3000 bytes.

As Hugh includes some hard-coded position information, it can only play the maps in the AITT map pool.

Hugh.h is the file with comments and line breaks that I used while developing, and Hugh.min.h is the version submitted for the tournament that has comments and unnecessary whitespace removed.

## Building

1. Download BWAPI 4.2.0
2. Rename Hugh.h to ExampleAIModule.h and overwrite the ExampleAIModule.h in the BWAPI example projects
3. Remove ExampleAIModule.cpp from the BWAPI example projects
4. Build the BWAPI example projects

Hugh will now be built to ExampleAIModule.dll.
