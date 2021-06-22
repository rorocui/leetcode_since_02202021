    else if( 3 <= row && row <= 5 && 0 <= col && col <= 2) return 1;
    else if( 6 <= row && row <= 8 && 0 <= col && col <= 2) return 2;
    /* 2nd 3-row && row */
    else if( 0 <= row && row <= 2 && 3 <= col && col <= 5) return 3;
    else if( 3 <= row && row <= 5 && 3 <= col && col <= 5) return 4;
    else if( 6 <= row && row <= 8 && 3 <= col && col <= 5) return 5;
    /* 3rd 3-row && row */
    else if( 0 <= row && row <= 2 && 6 <= col && col <= 8) return 6;
    else if( 3 <= row && row <= 5 && 6 <= col && col <= 8) return 7;
    else if( 6 <= row && row <= 8 && 6 <= col && col <= 8) return 8;
