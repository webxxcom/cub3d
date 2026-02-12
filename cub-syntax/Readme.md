# Cub3D Syntax Highlighting for VS Code

A Visual Studio Code extension that provides syntax highlighting for `.cub` map files used in the Cub3D project.

## Features

This extension highlights the following syntax elements:

- **Section headers** — `[TILES]`, `[MAP]`, `[DECORATIONS]`
- **Tile identifiers** — `NO`, `SO`, `WE`, `EA`, `F`, `C`
- **Map characters** — `0`, `1`, `N`, `S`, `E`, `W`
- **Decorations** — `DOOR`, `SPRITE`, `LIGHT`
- **Values** — Numbers, RGB colors, file paths, and comments

## Installation

### Quick Install

Run the following command to install the extension globally:

```bash
mkdir -p ~/.vscode/extensions/cub-syntax/syntaxes
mv cub-syntax/package.json ~/.vscode/extensions/cub-syntax/
mv cub-syntax/syntaxes/cub.tmLanguage.json ~/.vscode/extensions/cub-syntax/syntaxes/
```

After running this command, restart VS Code and the syntax highlighting should work automatically.

### Troubleshooting

If syntax highlighting doesn't work after installation, you need to associate `.cub` files with the syntax highlighter.

**Add this to your `.vscode/settings.json` file:**

```json
{
  "files.associations": {
    "*.cub": "cub"
  }
}
```

You can open your settings file by:
1. Press `Cmd+Shift+P` (Mac) or `Ctrl+Shift+P` (Windows/Linux)
2. Type "Preferences: Open User Settings (JSON)"
3. Add the file association above

## Usage

Once installed, open any `.cub` file in VS Code and enjoy automatic syntax highlighting!

## Support

If you encounter any issues, please ensure:
- The extension files are in the correct directory (`~/.vscode/extensions/cub-syntax/`)
- VS Code has been restarted after installation
- File associations are properly configured in your settings