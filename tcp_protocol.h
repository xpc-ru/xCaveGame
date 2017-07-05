#ifndef TCP_PROTOCOL_H_VER01
#define TCP_PROTOCOL_H_VER01
//This file defines 

#define TCP_PROTOCOL_VER 0x01
#define XCG_PORT         7500

#define SEND_PROT_VER 0x00
//0x00 - command
//0x** - version
//out: bool: canPlay
//           if FALSE connection dies 

#define MOVE_PLAYER 0x01
//0x01 - command
//bool - bHost
//       -true: hoster action
//       -false: client action
//byte - direction
//       up = 0; down = 1; left = 2; right = 3
//qpoint player_pos
//       int x {from 0 to 80}
//       int y {from 0 to 60}
//out: bool: canGo
//           if TRUE player moves everywhere

#define PLACE_BLOCK 0x02
//0x02 - command
//bool - bHost (same as in 0x01)
//ushort id {from 0 to 767}
//qpoint block_pos (same as in 0x01)
//qpoint pos (same as in 0x01)
//out: bool: placed
//           if TRUE block places

#define BREAK_BLOCK 0x03
//0x01 - command
//bool - bHost (same as in 0x01)
//qpoint block_pos (same as in 0x01)
//qpoint pos (same as in 0x01)
//out: bool: breaked
//           if TRUE block disappears everywhere


#endif // TCP_PROTOCOL_H_VER01
