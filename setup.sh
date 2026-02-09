#!/bin/bash

# Setup script for Snake Game - SFML Edition
# Installs SFML dependencies and compiles the game

echo "🐍 Snake Game - Setup Script"
echo "=============================="
echo ""

# Detect OS
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
    echo "📱 Detected: macOS"
    
    # Check if Homebrew is installed
    if ! command -v brew &> /dev/null; then
        echo "❌ Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    
    echo "📦 Installing SFML with Homebrew..."
    brew install sfml
    
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
    echo "🐧 Detected: Linux"
    
    # Detect Linux distribution
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        if [[ "$ID" == "ubuntu" || "$ID" == "debian" ]]; then
            echo "📦 Installing SFML with apt..."
            sudo apt-get update
            sudo apt-get install -y libsfml-dev
        elif [[ "$ID" == "fedora" ]]; then
            echo "📦 Installing SFML with dnf..."
            sudo dnf install -y SFML-devel
        else
            echo "⚠️  Unknown Linux distribution. Please install SFML manually."
        fi
    fi
    
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "❌ This script doesn't support Windows yet."
    echo "Please follow the manual installation steps in README.md"
    exit 1
else
    echo "❌ Unknown OS: $OSTYPE"
    exit 1
fi

# Check if compilation tools are available
if ! command -v g++ &> /dev/null; then
    echo "❌ g++ compiler not found. Please install build tools."
    exit 1
fi

if ! command -v make &> /dev/null; then
    echo "❌ Make not found. Please install make."
    exit 1
fi

echo ""
echo "✅ Dependencies installed successfully!"
echo ""
echo "🔨 Compiling the game..."
make re

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Compilation successful!"
    echo ""
    echo "🎮 To play, run: ./jeu"
    echo ""
else
    echo ""
    echo "❌ Compilation failed. Please check the errors above."
    exit 1
fi
