#!/bin/bash

# Проверяем, что переданы аргументы
if [ $# -ne 2 ]; then
  echo "Использование: $0 <ссылка на репозиторий> <название директории>"
  exit 1
fi

# Аргументы
TARGET_DIR=$1
REPO_URL=$2

# Создание директории
mkdir -p "$TARGET_DIR"

# Переход в созданную директорию
cd "$TARGET_DIR"

# Клонирование репозитория
git clone "$REPO_URL" .

# Переход в директорию репозитория
REPO_NAME=$(basename "$REPO_URL" .git)
cd src/

git switch develop

cp /Users/suzetten/dotfiles/Scratches/.clang-format .
cp /Users/suzetten/Reviews/test.sh .

ls
# Вывод текущей директории для подтверждения
#echo "Текущая директория: $(pwd)"
