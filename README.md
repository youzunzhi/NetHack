# README

An imitation of the classic game [NetHack](https://www.nethack.org/index.html).

## Getting Started

```shell
make
./nethack
```

Enter your name then start the game.

## Guide

The goal, interface and commands are pretty similar to the original NetHack game.

### Goal

Get `Yendor` before you die.

### Interface

#### The message line (top)

The top line of the screen is reserved for messages that describe things that are impossible to represent visually. If you see a “−−More−−” on the top line, this means that NetHack has another message to display on the screen, but it wants to make certain that you've read the one that is there first. To read the next message, just press the space bar. 

#### The status lines (bottom)

The bottom two lines of the screen contain several cryptic pieces of information describing your current status: your name, Strength, Defense, current Dungeon level, Gold, Hit Points and Current Turns.

#### The map (rest of the screen)

| Symbols | Meaning                            |
| ------- | ---------------------------------- |
| @       | Hero (You)                      |
| \| or - | Walls                              |
| #       | Corridor                           |
| A-Z     | Inhabitants of the Mazes of Menace |
|	Y				|	The Amulet of Yendor							 |
| $       | A pile of Gold                     |
| !       | A potion                           |
| [       | A suit or piece of armor           |
| )       | A weapon                           |
| > | Stairs down. |
| < | Stairs up. |

### Commands

| Keys       | Commands                                      |
| ---------- | --------------------------------------------- |
| [yuhjklbn] | 8 directions to move your character or attack |
| K          | Kick Door                                     |
| c          | Close Door                                    |
| .          | Rest for a turn                               |
| >          | Go downstairs                                 |
| <          | Go upstairs                                   |
| ,          | Pick up items                                 |
| i          | Show your Backpack                            |
| d          | Drop items                                    |
| w          | Wield a weapon                                |
| W          | Wear an Armor                                 |
| a          | Apply an item                                 |
| q          | Quit game                                     |

