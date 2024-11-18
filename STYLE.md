# Style Guide 📝

## Codebase
### Length of a line
A line must not exceed 80 characters. 
### Naming Conventions

| Type | Case Style | Example |
|------|------------|---------|
| Variables | snake_case | `window_screen`, `character_health` |
| Functions | camelCase | `getScore()`, `updatePosition()` |
| Classes | PascalCase | `GameEngine`, `PlayerCharacter` |

### Comments and tags
#### Comments
This might seem a little weird to you but for comments, use the following:

```
/*
NOTE:
   - <Comment 1>

   - <Comment 2>
*/
```
It's not standard but it's what we've been using and it's been bloating the code up a little bit but at least it is consistent.

#### Tags
We have the following tags:

```
/*
SECTION <X>: <SHORT DESCRIPTION OF THE SECTION>
*/
```

```
/*
DESCRIPTION: <Description of a function>
*/
```

## Git and GitHub
### Tags
| Tag | Use |
|-----|-----|
| feat | New features |
| fix | Bug fixes |
| art | Visual and art-related |
| docs | Documentation changes |
| style | Formatting, semicolons, etc |
| refactor | Code restructuring |
| test | Adding/modifying tests |
| chore | Maintenance tasks |

### Commit messages
The format is as follows:
```
<tag>: <concise description>
```
For example:
```
chore: update the game loop
style: Format code to match 80 character limit
```
### Pull Requests
Should be similar to a commit message.
```
<tag>: <brief description>
```
For example:
```
fix: memory leak in the Sprite class
feat: add player inventory system
```
 