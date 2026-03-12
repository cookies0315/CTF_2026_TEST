# CTF_2026_TEST

這是一個針對大學資安課程設計的 Use-After-Free 漏洞練習環境。

## 目錄

- [環境需求](#環境需求)
- [練習題目](#練習題目)
- [CTF 挑戰](#ctf-挑戰)
- [快速開始](#快速開始)
- [攻擊方式說明](#攻擊方式說明)
- [防禦方式](#防禦方式)

---

## 環境需求

- Kali Linux（或任何 Linux 發行版）
- GCC 編譯器
- AddressSanitizer (ASan)

## 驗證環境

```bash
gcc --version
```

---

## 練習題目

| 編號 | 名稱 | 難度 | 描述 |
|------|------|------|------|
| uaf_01 | 基本 UAF | ⭐ | 最簡單的 Use-After-Free |
| uaf_02 | Double Free | ⭐ | 多次釋放同一記憶體 |
| uaf_03 | Buffer Overflow | ⭐ | 越界寫入記憶體 |
| uaf_04 | 懸空指標 | ⭐⭐ | 指標超出作用域 |
| uaf_05 | 結構體 UAF | ⭐⭐ | 結構體的 UAF |
| uaf_06 | 正確範例 | - | 安全程式碼示範 |
| uaf_07 | Heap Spray | ⭐⭐⭐ | 記憶體佈局控制 |
| uaf_08 | CTF 挑戰 | ⭐⭐⭐⭐ | 綜合漏洞利用 |

---

## 詳細題目說明

### uaf_01 - 基本 UAF (Basic Use-After-Free)

**說明**：示範最基本的 Use-After-Free 漏洞。記憶體被 `free()` 釋放後，指標仍然指向該記憶體位址，繼續使用該指標會造成 UAF 漏洞。

**原始碼重點**：
```c
char *ptr = (char *)malloc(100);
strcpy(ptr, "Hello World");
free(ptr);
printf("%s", ptr);  // UAF: 使用已釋放的記憶體
```

**執行方式**：
```bash
./uaf_01
```

**ASan 輸出範例**：
```
=================================================================
==12345==ERROR: AddressSanitizer: heap-use-after-free on address 0x602000000010
```

---

### uaf_02 - Double Free (雙重釋放)

**說明**：示範 Double Free 漏洞。對同一個指標呼叫兩次 `free()`，會導致 heap corruption，可能被攻擊者利用進行記憶體佈局控制。

**原始碼重點**：
```c
char *ptr1 = (char *)malloc(100);
free(ptr1);
free(ptr1);  // Double Free!
```

**執行方式**：
```bash
./uaf_02
```

**ASan 輸出範例**：
```
=================================================================
==12345==ERROR: AddressSanitizer: double-free on address 0x602000000010
```

---

### uaf_03 - Buffer Overflow (緩衝區溢位)

**說明**：示範經典的 Buffer Overflow 漏洞。使用不安全的輸入函數，沒有邊界檢查，導致資料溢位。

**原始碼重點**：
```c
char buffer[32];
fgets(buffer, sizeof(buffer), stdin);  // 輸入超過 32 字元會溢位
```

**執行方式**：
```bash
./uaf_03
```

**攻擊方式**（嘗試超過 32 字元的輸入）：
```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```

---

### uaf_04 - 懸空指標 (Dangling Pointer)

**說明**：指標指向的記憶體已經被釋放，但指標本身仍然存在並可被使用。

**原始碼重點**：
```c
char *create_dangling_pointer() {
    char *ptr = (char *)malloc(100);
    strcpy(ptr, "Temporary data");
    return ptr;  // ptr 指向的記憶體在函數結束後仍存在，但指標變成懸空指標
}
```

**執行方式**：
```bash
./uaf_04
```

---

### uaf_05 - 結構體 UAF (Struct UAF)

**說明**：示範結構體記憶體釋放後的 UAF 漏洞，可以透過結構體成員存取已釋放的記憶體。

**原始碼重點**：
```c
struct User {
    char username[32];
    char password[32];
    int is_admin;
};

struct User *user = malloc(sizeof(struct User));
user->is_admin = 0;
free(user);
printf("%d", user->is_admin);  // UAF: 存取已釋放的結構體
```

**執行方式**：
```bash
./uaf_05
```

---

### uaf_06 - 正確範例 (Safe Example)

**說明**：示範如何安全地處理記憶體，避免 UAF 漏洞。

**原始碼重點**：
```c
char *ptr = (char *)malloc(100);
strcpy(ptr, "Hello World");
free(ptr);
ptr = NULL;  // 重要：設為 NULL 防止 UAF

if (ptr != NULL) {
    printf("%s", ptr);  // 不會執行
}
```

**執行方式**：
```bash
./uaf_06
```

**防禦重點**：
1. `free()` 後立即設為 `NULL`
2. 使用前檢查指標是否為 `NULL`
3. 使用安全的記憶體管理函數

---

### uaf_07 - Heap Spray (堆噴灑)

**說明**：示範 Heap Spray 技術。透過大量配置記憶體來控制堆積佈局，常用於漏洞利用。

**原始碼重點**：
```c
#define SPRAY_SIZE 1000
char *ptrs[SPRAY_SIZE];

for (int i = 0; i < SPRAY_SIZE; i++) {
    ptrs[i] = (char *)malloc(256);
    memset(ptrs[i], 'A', 256);  // 填充特定資料
}

// 之後的配置可能會落在這些位置
```

**執行方式**：
```bash
./uaf_07
```

**應用場景**：
- 控制記憶體佈局
- 配合 UAF 進行漏洞利用
- 劫持程式執行流程

---

### uaf_08 - CTF 挑戰 (CTF Challenge)

**說明**：綜合利用 UAF 和 Buffer Overflow 的 CTF 挑戰。

**目標**：取得 admin 權限，獲得 FLAG

**FLAG**：`FLAG{U4f_3xp10t_5ucc3ssful}`

**功能**：
```
1. Register new account    - 註冊帳號
2. Login                  - 登入
3. View Profile           - 查看個人資料
4. Admin Panel            - 管理員面板（需要 admin 權限）
5. Delete Account         - 刪除帳號（觸發 UAF）
6. Secret Admin Upgrade   - 秘密管理員升級
7. Debug Info             - 除錯資訊
8. Exit                   - 離開
```

#### 攻擊方法一：Buffer Overflow（簡單）

```
1. 選擇 1 (Register)
2. 輸入 username: 超過 32 個字元
   AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
3. 輸入 password: 任意
4. 選擇 4 (Admin Panel)
5. 取得 FLAG！
```

**原理**：
```c
struct User {
    char username[32];   // 0-31
    char password[32];  // 32-63  
    int is_admin;       // 64-67 ← 覆蓋這個位置
};
```

#### 攻擊方法二：Use-After-Free（較難）

```
1. 選擇 1 (Register)         → 註冊帳號
2. 選擇 6 (Admin Upgrade)  → 設定 is_admin = 1
3. 選擇 4 (Admin Panel)    → 確認可見 FLAG
4. 選擇 5 (Delete)          → free 記憶體
5. 選擇 1 (Register)        → 重新註冊
6. 選擇 4 (Admin Panel)    → 再次取得 FLAG！
```

**執行方式**：
```bash
./uaf_08
```

---

## CTF 挑戰

### uaf_08 - 漏洞綜合利用挑戰

**目標**：取得 admin 權限，獲得 FLAG

**FLAG**：`FLAG{U4f_3xp10t_5ucc3ssful}`

### 挑戰功能

```
1. Register new account    - 註冊帳號
2. Login                  - 登入
3. View Profile           - 查看個人資料
4. Admin Panel            - 管理員面板（需要 admin 權限）
5. Delete Account         - 刪除帳號（觸發 UAF）
6. Secret Admin Upgrade   - 秘密管理員升級
7. Debug Info             - 除錯資訊
8. Exit                   - 離開
```

### 攻擊方式

#### 方法一：Buffer Overflow（簡單）

```
1. 選擇 1 (Register)
2. 輸入 username: 超過 32 個字元 (例如 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA)
3. 輸入 password: 任意
4. 選擇 4 (Admin Panel)
5. 取得 FLAG！
```

**原理**：

```
struct User {
    char username[32];   // 0-31
    char password[32];  // 32-63  
    int is_admin;       // 64-67 ← 超過 32 字元會覆蓋這裡
};
```

#### 方法二：Use-After-Free（較難）

```
1. 選擇 1 (Register)         → 註冊帳號
2. 選擇 6 (Admin Upgrade)  → 設定 is_admin = 1
3. 選擇 4 (Admin Panel)    → 確認可見 FLAG
4. 選擇 5 (Delete)          → free 記憶體
5. 選擇 1 (Register)        → 重新註冊
6. 選擇 4 (Admin Panel)    → 再次取得 FLAG！
```

---

## 快速開始

### 編譯所有練習

```bash
cd CTF2026/0312TEST
./build_all.sh
```

### 執行 ASan 練習

```bash
# 基本練習（使用 ASan 檢測）
cd 0312TEST
./uaf_01
./uaf_02
# ...
```

### 執行 CTF 挑戰

```bash
# CTF 挑戰（無 ASan，讓漏洞存在）
cd 0312TEST
./uaf_08
```

---

## 攻擊方式說明

### Use-After-Free (UAF)

**定義**：記憶體被 `free()` 釋放後，指標仍被使用

**範例**：

```c
char *ptr = malloc(100);
free(ptr);       // 記憶體已釋放
printf("%s", ptr);  // 錯誤：仍在使用已釋放的記憶體
```

**防禦**：

```c
free(ptr);
ptr = NULL;  // 永遠設為 NULL
```

### Buffer Overflow

**定義**：寫入資料超過緩衝區大小

**範例**：

```c
char buffer[32];
scanf("%s", buffer);  // 無邊界檢查！
```

**防禦**：

```c
scanf("%31s", buffer);  // 限制長度
fgets(buffer, sizeof(buffer), stdin);  // 使用安全函數
```

---

## 檔案結構

```
CTF2026/
├── README.md                 # 本檔案
└── 0312TEST/                 # UAF 練習實驗室
    ├── build_all.sh          # 編譯腳本
    ├── uaf_01_basic.c        # 練習 1-7 原始碼
    ├── uaf_02_double_free.c
    ├── uaf_03_buffer_overflow.c
    ├── uaf_04_dangling_pointer.c
    ├── uaf_05_struct.c
    ├── uaf_06_fixed.c
    ├── uaf_07_heap_spray.c
    ├── uaf_08_ctf.c          # CTF 挑戰原始碼
    └── uaf_01 ~ uaf_08       # 編譯後的執行檔
```

---

## 參考資源

- [AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html)
- [how2heap](https://github.com/shellphish/how2heap)
- [CVE-2026-2441](https://nvd.nist.gov/vuln/detail/CVE-2026-2441)
