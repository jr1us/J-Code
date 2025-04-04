/*
*
*   - Author: jrius ( vk.com/s.fridom | t.me/dcapybarov ) -
*   - Include: J-Code ( The J-Code Protector ) -
*
*   - Include J-Code ������������� ��������� �������:
*
*    * EncodeString(dest[], const source[], max_len = sizeof(dest)) :
*       * �������� ������ `source` � ��������� ��������� � `dest`.
*       * max_len - ��� ������������ ����� �������������� ������.
*
*    * DecodeString(dest[], const source[], max_len = sizeof(dest)) :
*       * ���������� ������ `source` � ��������� ��������� � `dest`.
*       * max_len - ��� ������������ ����� �������������� ������.
*
*    ��� ������� ���������� �������� ����������� ������, ������������ ����� ������������ ������ � ����� ������ (���� ��� ������������) ���� �����������, �� ��������� ��������� `DEFAULT_SECURITY_SHIFT`.
*
*    ������ ���������� �� ������ ����������� 3.10.8
*    ���������� ������ - https://github.com/jr1us/J-Code/releases/tag/Pawn
*/

const MAX_SIZE_HASH_PASSWORD = 128;
const DEFAULT_SECURITY_SHIFT = 5;

stock GetShift(const source[], &shift, &has_digit) {
    new  len = strlen(source);

    has_digit = (len > 0 && source[len-1] >= '0' && source[len - 1] <= '9');
    shift = has_digit ? (source[len-1] - '0') : DEFAULT_SECURITY_SHIFT;
    
    return has_digit ? (len - 1) : len;
}

stock EncodeString(dest[], const source[], max_len = sizeof(dest)) {
    if (max_len <= 0 || max_len > MAX_SIZE_HASH_PASSWORD) return 0;

    new shift, has_digit,
        len = GetShift(source, shift, has_digit),
        i = 0;
    
    for ; i < len && i < max_len - 1; i++ do {
        dest[i] = (source[i] >= 'A' && source[i] <= 'Z') ? ('A' + ((source[i] - 'A' + shift) % 26)) : 
                 (source[i] >= 'a' && source[i] <= 'z') ? ('a' + ((source[i] - 'a' + shift) % 26)) : 
                 source[i];
    }
    
    if (has_digit && i < max_len - 1) {
        dest[i++] = source[len];
    }
    
    dest[i] = '\0';
    return 1;
}

stock DecodeString(dest[], const source[], max_len = sizeof(dest)) {
    if (max_len <= 0 || max_len > MAX_SIZE_HASH_PASSWORD) return 0;

    new shift, has_digit,
        len = GetShift(source, shift, has_digit),
        i = 0;
    
    for ; i < len && i < max_len - 1; i++ do {
        dest[i] = (source[i] >= 'A' && source[i] <= 'Z') ? ('A' + ((source[i] - 'A' - shift + 26) % 26)) : 
                 (source[i] >= 'a' && source[i] <= 'z') ? ('a' + ((source[i] - 'a' - shift + 26) % 26)) : 
                 source[i];
    }
    
    if (has_digit && i < max_len - 1) {
        dest[i++] = source[len];
    }
    
    dest[i] = '\0';
    return 1;
}