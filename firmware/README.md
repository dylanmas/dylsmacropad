# Macro schematic:

```c++
case '<CHAR>':
      active = "<MACRO NAME>";
      <MACRO KEYBOARD/MOUSE FUNCTIONS>
      break;  
```

## CHAR
CHAR corresponds with the macro's name. This is used editable via editing the code or using the software. As a result of char being the case condition, the macro's case statement is referred to by its name.
## MACRO NAME
In place of MACRO NAME will also be the macro's name. Thus, its value is the same as the CHAR placeholder. This variable is used to properly highlight the pressed key on the display.
## MACRO KEYBOARD/MOUSE FUNCTIONS
This is where mouse and keyboard commands are. Key commands can be broken down into four types:
### Letters and numbers:
This type includes all letters, numbers, and symbols.
```
//pressing once
Keyboard.write();

//holding, then releasing
Keyboard.press();
Keyboard.release();
```
Software code:
```
['<LET/NUM/SYM AS STRING>'[<ADDITIONAL CODE WHILE PARENT IS HELD DOWN>]]
```
### Modifier keys:
- Control
- Left/right alt
- Win/super
- Esc
```
//pressing once
Keyboard.write();

//holding, then releasing
Keyboard.press();
Keyboard.release();
```
Software code:
```
[:<MOD>:[<ADDITIONAL CODE WHILE PARENT IS HELD DOWN>]]
```
### External keys:
- Backspace
- Enter
- Space
- Arrow keys
- Page up/down
- Home/end
- Left/right shift
- Delete
- Tab
- Print screen
- SysRq
```
//pressing once
Keyboard.write();

//holding, then releasing
Keyboard.press();
Keyboard.release();
```
Software code:
```
[:<EXT>:[<ADDITIONAL CODE WHILE PARENT IS HELD DOWN>]]
```
### Special keys:
Layer change keys fall under this type. These keys will change the macro pad's key layer.
```
//Layer up

//Layer down

```
Software code:
```
LD (layer down)
LU (layer up)
```
Note: Additional key presses cannot be added to special keys.