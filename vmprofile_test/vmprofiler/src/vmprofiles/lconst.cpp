#include <vmprofiler.hpp>

namespace vm::handler::profile
{
    vm::handler::profile_t lconstq = {
        // MOV RAX, [RSI]
        // SUB RBP, 8
        // MOV [RBP], RAX
        "LCONSTQ",
        LCONSTQ,
        64,
    {{// MOV RAX, [RSI]
        [](const zydis_decoded_instr_t& instr)  // MOV RAX, [RSI]
        -> bool {
          return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                 instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                 instr.operands[0].reg.value == ZYDIS_REGISTER_RAX &&
                 instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                 instr.operands[1].size == 64;
        },  
                // SUB RBP, 8
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x8;
            },
            // MOV [RBP], RAX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_RAX;
        },
            }},
    vm::handler::extention_t::none
    };

    vm::handler::profile_t lconstdw = {
        // SUB RBP, 4
        // MOV [RBP], EAX
        "LCONSTDW",
        LCONSTDW,
        32,
            {{[](const zydis_decoded_instr_t& instr)  // MOV EAX, [RSI]
              -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                       instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[0].reg.value == ZYDIS_REGISTER_EAX &&
                       instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[1].size == 32;
              },
                // SUB RBP, 4
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x4;
            },
            // MOV [RBP], EAX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_EAX;
            } } } ,vm::handler::extention_t::none,
    };

    vm::handler::profile_t lconstw = {
        // SUB RBP, 2
        // MOV [RBP], AX
        "LCONSTW",
        LCONSTW,
        16,
        { { 
             [](const zydis_decoded_instr_t& instr)  // MOV AX, [RSI]
                  -> bool {
                   return (instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                          instr.operands[0].type ==
                              ZYDIS_OPERAND_TYPE_REGISTER &&
                          instr.operands[0].reg.value == ZYDIS_REGISTER_AX &&
                          instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                          instr.operands[1].mem.base == ZYDIS_REGISTER_RSI &&
                          instr.operands[1].size == 16);
              },
                // SUB RBP, 2
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x2;
            },
            // MOV [RBP], AX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_AX;
            } } } ,
            vm::handler::extention_t::none
    };

    vm::handler::profile_t lconstbzxw = {
        // MOV AL, [RSI]
        // SUB RBP, 2
        // MOV [RBP], AX
        "LCONSTBZXW",
        LCONSTBZXW,
        8,
        { {[](const zydis_decoded_instr_t& instr)  // movzx   eax, byte ptr [rsi]
              -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOVZX &&
                       instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[0].reg.value == ZYDIS_REGISTER_EAX &&
                       instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[1].size == 8;
              },
                // SUB RBP, 2
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x2;
            },
            // MOV [RBP], AX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_AX;
            } } },
            vm::handler::extention_t::none,
    };

    vm::handler::profile_t lconstb2w = {
        // MOV AL, [RSI]
        // SUB RBP, 2
        // MOV [RBP], AX
        "LCONSTB2W",
        LCONSTB2W,
        8,
        {{[](const zydis_decoded_instr_t& instr)  // mov     al, [rsi]
          -> bool {
            return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                   instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   instr.operands[0].reg.value == ZYDIS_REGISTER_AL &&
                   instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   instr.operands[1].size == 8;
          },
          // SUB RBP, 2
          [](const zydis_decoded_instr_t& instr) -> bool {
            return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                   instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   instr.operands[0].reg.value == ZYDIS_REGISTER_RBP &&
                   instr.operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                   instr.operands[1].imm.value.u == 0x2;
          },
          // MOV [RBP], AX
          [](const zydis_decoded_instr_t& instr) -> bool {
            return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                   instr.operands[0].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                   instr.operands[0].mem.base == ZYDIS_REGISTER_RBP &&
                   instr.operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                   instr.operands[1].reg.value == ZYDIS_REGISTER_AX;
          }}},
        vm::handler::extention_t::none,
    };

    vm::handler::profile_t lconstbsxdw = {
        // CWDE
        // SUB RBP, 4
        // MOV [RBP], EAX
        "LCONSTBSXDW",
        LCONSTBSXDW,
        16,
        { { 
                [](const zydis_decoded_instr_t& instr)  // MOV AX, [RSI]
              -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                       instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[0].reg.value == ZYDIS_REGISTER_AX &&
                       instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[1].size == 16;
              },
                // CWDE
            []( const zydis_decoded_instr_t &instr ) -> bool { return instr.mnemonic == ZYDIS_MNEMONIC_CWDE; },
            // SUB RBP, 4
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x4;
            },
            // MOV [RBP], EAX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_EAX;
            } } },
        vm::handler::extention_t::sign_extend,
    };

    vm::handler::profile_t lconstbsxq = {
        // CDQE
        // SUB RBP, 0x8
        // MOV [RBP], RAX
        "LCONSTBSXQ",
        LCONSTBSXQ,
        32,
        { { 
          [](const zydis_decoded_instr_t& instr) // mov     eax, [rsi]
              -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                       instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER&&
                       instr.operands[0].reg.value == ZYDIS_REGISTER_EAX &&
                       instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY&&
                       instr.operands[1].size == 32;
          },
            // CDQE
            []( const zydis_decoded_instr_t &instr ) -> bool { return instr.mnemonic == ZYDIS_MNEMONIC_CDQE; },
            // SUB RBP, 0x8
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x8;
            },
            // MOV [RBP], RAX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_RAX;
            } } },
        vm::handler::extention_t::sign_extend,
    };

    vm::handler::profile_t lconstdwsxq = {
        // CDQE  0x8xxxxxxx -> 0xffffffff8xxxxxxx
        // SUB RBP, 8
        // MOV [RBP], RAX
        "LCONSTDWSXQ",
        LCONSTDWSXQ,
        32,
        { 
          [](const zydis_decoded_instr_t& instr)  // mov     eax, [rsi]
         -> bool {
           return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                  instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                  instr.operands[0].reg.value == ZYDIS_REGISTER_EAX &&
                  instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                  instr.operands[1].size == 32;
         },
            // CDQE
          []( const zydis_decoded_instr_t &instr ) -> bool { return instr.mnemonic == ZYDIS_MNEMONIC_CDQE; },
          // SUB RBP, 8
          []( const zydis_decoded_instr_t &instr ) -> bool {
              return instr.mnemonic == ZYDIS_MNEMONIC_SUB && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                     instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                     instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE && instr.operands[ 1 ].imm.value.u == 0x8;
          },
          // MOV [RBP], RAX
          []( const zydis_decoded_instr_t &instr ) -> bool {
              return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                     instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                     instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                     instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_RAX;
          } },
        vm::handler::extention_t::sign_extend,
    };

    vm::handler::profile_t lconstwsxq = {
        // CWDE
        // CDQE
        // SUB RBP, 8
        // MOV [RBP], RAX
        "LCONSTWSXQ",
        LCONSTWSXQ,
        8,
        { { 
            [](const zydis_decoded_instr_t& instr)  // movzx   eax, byte ptr [rsi]
              -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOVZX &&
                       instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[0].reg.value == ZYDIS_REGISTER_EAX &&
                       instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[1].size == 8;
              },    
            // CWDE
            []( const zydis_decoded_instr_t &instr ) -> bool { return instr.mnemonic == ZYDIS_MNEMONIC_CWDE; },
            // CDQE
            []( const zydis_decoded_instr_t &instr ) -> bool { return instr.mnemonic == ZYDIS_MNEMONIC_CDQE; },
            // SUB RBP, 8
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x8;
            },
            // MOV [RBP], RAX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_RAX;
            } } },
        vm::handler::extention_t::sign_extend
    };

    vm::handler::profile_t lconstwsxdw = {
        // CWDE
        // SUB RBP, 4
        // MOV [RBP], EAX
        "LCONSTWSXDW",
        LCONSTWSXDW,
        16,
            {{[](const zydis_decoded_instr_t& instr)  // MOV AX, [RSI]
              -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV &&
                       instr.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[0].reg.value == ZYDIS_REGISTER_AX &&
                       instr.operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[1].size == 16;
              },
                // CWDE
            []( const zydis_decoded_instr_t &instr ) -> bool { return instr.mnemonic == ZYDIS_MNEMONIC_CWDE; },
            // SUB RBP, 4
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_SUB &&
                       instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 0 ].reg.value == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_IMMEDIATE &&
                       instr.operands[ 1 ].imm.value.u == 0x4;
            },
            // MOV [RBP], EAX
            []( const zydis_decoded_instr_t &instr ) -> bool {
                return instr.mnemonic == ZYDIS_MNEMONIC_MOV && instr.operands[ 0 ].type == ZYDIS_OPERAND_TYPE_MEMORY &&
                       instr.operands[ 0 ].mem.base == ZYDIS_REGISTER_RBP &&
                       instr.operands[ 1 ].type == ZYDIS_OPERAND_TYPE_REGISTER &&
                       instr.operands[ 1 ].reg.value == ZYDIS_REGISTER_EAX;
            } } },
        vm::handler::extention_t::sign_extend,
    };
    } // namespace vm::handler::profile