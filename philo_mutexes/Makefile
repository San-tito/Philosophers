# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 14:46:46 by sguzman           #+#    #+#              #
#    Updated: 2024/06/09 02:09:41 by sguzman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		= philo 
CC 		= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread
DFLAGS		= -MMD -MF $(@:.o=.d)

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_PATH	= ./src

OBJS_PATH 	= ./build

INCLUDE_PATH	= ./include

HEADER		= $(INCLUDE_PATH)/philo.h

SRCS 		= error.c parse.c routine.c thread.c time.c waiter.c xmalloc.c

MAIN 		= philo.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

OBJS		= $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.o})

OBJS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.o})

DEPS		= $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.d})

DEPS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.d})

################################################################################
#                                 Makefile logic                               #
################################################################################

SHELL = /bin/bash
RED         	= \033[0;31m
GREEN       	= \033[0;32m
YELLOW      	= \033[0;33m
BLUE        	= \033[0;34m
PURPLE      	= \033[0;35m
CYAN        	= \033[0;36m
RESET       	= \033[m

define run
    printf "%b%-46b" "$(BLUE)$(2) " "$(CYAN)$(@F)$(RESET)"; \
    OUTPUT=$$($(1) 2>&1); \
    RESULT=$$?; \
    if [ $$RESULT -ne 0 ]; then \
        printf "%b\n" "$(RED)[✗]$(RESET)"; \
	printf "%b\n" "$$OUTPUT"; \
    else  \
        printf "%b\n" "$(GREEN)[✓]$(RESET)"; \
    fi; \
    [ $$RESULT -eq 0 ]
endef

################################################################################
#                                 Makefile rules                               #
################################################################################

all: banner $(NAME) 

banner:
	@printf "%b" "$(PURPLE)"
	@echo
	@echo "                                          ░░░░░░░░░░▒▒░░░░░░░░  "
	@echo "                                          ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"
	@echo "                                          ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"
	@echo "                                            ░░▒▒▒▒▒▒▒▒▒▒▒▒░░░░  "
	@echo "                                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░  "
	@echo "                                              ▒▒▒▒▓▓██▓▓▓▓▒▒    "
	@echo "                                              ▓▓▓▓▓▓████▓▓▒▒    "
	@echo "                                              ▓▓▓▓▓▓██▓▓▓▓▒▒    "
	@echo "                                            ░░▓▓▓▓▓▓████▓▓▒▒    "
	@echo "                                          ░░  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░  "
	@echo "                                              ▓▓▓▓▓▓▓▓▓▓▓▓▒▒    "
	@echo "                                            ░░▒▒▓▓▓▓████▓▓▓▓    "
	@echo "                                              ▓▓▓▓▓▓██▓▓▓▓▒▒    "
	@echo "                                            ░░▓▓▓▓▓▓████▓▓▒▒    "
	@echo "                                        ░░    ▓▓▓▓▓▓████▓▓▓▓    "
	@echo "░░░░░░                                ░░  ░░▒▒▒▒▒▒░░▒▒░░░░░░    "
	@echo "    ░░    ░░    ░░░░  ░░░░        ░░      ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░"
	@echo "                                          ▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒"
	@echo
	@printf "%b" "$(RESET)"

-include $(DEPS) $(DEPS_MAIN)
$(NAME):	$(OBJS) $(OBJS_MAIN)
			@$(call run, $(CC) $(CFLAGS) $(DFLAGS) -I $(INCLUDE_PATH) $^ -o $@, "Building")

$(OBJS_PATH)/%.o: 	$(SRCS_PATH)/%.c $(HEADER) Makefile
			@mkdir -p $(dir $@)
			@$(call run, $(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH), "Compiling")

clean:		banner
			@$(call run, rm -rf $(OBJS_PATH))

fclean:		banner clean
			@$(call run, rm -rf $(NAME))

re:			fclean all

.PHONY:		all clean fclean re banner
