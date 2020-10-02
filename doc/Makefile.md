# Makefile

This file is intended to be a quick reference for this project's Makefile,
as well as giving a little explanation of what a Makefile is, how they work
and why we are using them.

This document is intended for engineering freshmen. For the more curious among
the readers, I strongly suggest reading the make
[documentation](https://www.gnu.org/software/make/manual/make.html) from the
GNU project.


## What is a Makefile?

A Makefile is a set of instruction for the compiler. It
details the steps that produce the project's executable binary. This
is probably overwhelming, so let's try with an analogy.

The code you want the processor to run is called a binary. Let's say this
binary is a delicious [brownie](https://www.youtube.com/watch?v=Ixe_NYTSFwo):

- You can eat the brownie, just like the CPU can run a binary.
- You cannot (well, should not) eat raw eggs, flour, cacao powder, sugar and
	melted butter, just like the CPU cannot run the source code directly.

A binary is, *in essence*, the assembly instruction that the CPU understands,
but a human can't understand so easily. So the human write source code and
uses a program called a *compiler* to turn the source code into a binary.
In our brownie analogy, the compiler is the baker, the source files (the C
*code*) are the ingredients and the brownie is the binary.

So how exactly does the compiler know what to do with the source files?
Well, the same way the baker knows how to make the brownie; he follows a
recipe. If you've ever cooked anything, you know that simply mixing the
ingredients together does not produce the intended result.

This is where the Makefile comes in. The Makefile is thre *recipe* for
the compiler to turn the source files into a binary executable.

## How does a Makefile work?

Ok, so the Makefile is a set of instructions that tell the compiler what to
do, so we're done right? Well, not so fast. The compiler utility we are using
in most C programming is called GCC (the GNU Compiler Collection). In order to
compile the final binary, there are several intermediate steps. Most
importantly, we need to compile some source files individually, before
*linking* them together for the final binary. Like when making the brownie,
we combine the dry ingredients together and the wet ingredients together,
before combining them all together.

However, the compiler does not simply look at the Makefile and then compile
the program: this is done by the *GNU make* utility. Really, in our cooking
analogy, the make utility is the cook looking at the recipe. The Makefile
tells make what to do. That's it. The make utility can (and will) do anything
the recipe asks. It can set variables, set rules for compiling, install a
program, uninstall a program, etc. Since the possibilities are near endless,
listing them all would be futile and counter-productive. Instead, we detail
and document the currently used Makefile for the rocket_controller project
a bit further in this document.

Also worth noting is how make reads a makefile. This process is explained in
more details in the documentation, but here's a basic explanation:

1. The makefile and included makefiles are parsed, variables, their values,
	implicit and explicit rules are internalized and a dependency graph is built.
2. make uses this data to determine which targets need to be updated and runs
	the necessary recipes to update them.

## Why are we using Makefiles?

So for some readers this may seem like a lot of work. After all, why not use
python and forget about compiling anything in the first place? Or if we
absolutly want to use C, why not use an IDE that somehow does all the work for
us?

These questions are valid concerns and it is important to not dismiss them
by simply saying "That's the way we do it, get with it". After all,
development of the project would be faster if it were programmed in python,
or if we used an IDE (integrated development environment) to hide the magic
behind a graphical interface. So let us provide some answers and justification
for this seemingly masochistic process.

### Why not use *insert modern programming language*?

There are several reasons to prefer C over other languages in our situation.
First, this project was first developped for the Arduino platform in 2015
to 2017. Then, we ported it to the STM32F407 platform for 2018 and then again
switched to PIC32MZ in 2019. Finally, we are using a Raspberry Pi in 2020.
This switch occured as the participants in the project (both hardware and
firmware) improved their skills and wanted more performance out of the 
avionics.

Because the platform used in the future may change again, the reason for the
use of the C language becomes obvious. C is a highly portable and high
performance language. We can reuse code from the previous years and easily
port them to the new platform.

Another reason is simply that C is the most commonly used programming language
for embedded projects, so chosing the same language helps a lot when looking
for help online.

Finally, learning C is an essential part of the learning experience as a
computer science student. It forces the understanding of the underlying
hardware, as well as using the operating system's features to your advantage.

### Why not use an IDE?

The first reason is very simple: we have to compile for the target platform.
This can be acheived two ways:

1. Compiling on the target platform
2. Cross-compiling for the target platform, on another computer

Since setting up a cross compiling toolchain for the Raspberry Pi is a tedious
and error prone process, it is better to compile on the Raspberry Pi directly.
Cross-compiling is shown in the GIF-3004 course when students are 3 years into
the program. The setup is shown step by step with a protocole, the teacher and
two teaching assistants and even then it's a mess. So we won't attempt to show
it to you.

So we are left with compiling on the target platform. Since the distribution
we use does not have a desktop environment installed, we can't use an IDE on
the Raspberry Pi.

The other less pragmatic reason is simply because learning Makefile is a
valuable skill to have as a computer engineer (also learning is fun).

Also, making our own makefile gives us the total freedom and control
over the compilation process. We decide exactly what libraries to use,
what optimisations we want, etc.

Finally, we can use the `.PHONY` targets to install the program, run it
automatically, run unit tests, etc.

## Rocket controller Makefile explanation

The Makefile used for the project is still a work in progress, but we can
examine and explain it for everyone's benefit.

### Variables

At the top of the file, we see a bunch of variable assignments. Here's what
they all mean.

First, the variable CC is set to 'cc'. CC stands for C Compiler, this is where
we choose what compiler we want make to use to compile our C source files.

Next, the name of the project is defined. This variable is used to name the
final binary's name.

Then, a list of object files is defined. Objects are the result of compiling,
but not linking, some source files.

Then we have the library flags `LFLAGS`, which are used to link important
external libraries to the project. For now, we only use the pthread library,
so only have '-lpthread'. The '-l' is the option flag passed to the compiler
that tells it to link the library 'pthread'. If we were to have more than 1
library, the variable would look like: `LFLAGS = -lpthread -lmath`.

Next, the CFLAGS variable defines various options passed to the compiler.
For instance, the -Wall option tells the compiler to enable all warnings.

### Rules

The first rule of the makefile is the first rule to be run by make. The syntax
of the rule is as follows:

```
targets : prerequisites
        recipe
        ...
```

So for the first rule, the target is `all`, the prerequisites are all of our
object files and the recipe is to order our compiler `cc` to link all of our
prerequisites object files `$^` to generate the output file `rocket_controller`
`-o $(MAIN)` using the linked libraries `LFLAGS` and options `CFLAGS` we want.

So far all the variables are pretty straight forward, but what about that
`$^`? This is called an 'automatic variable'. The GNU make documentation goes
in more detail about what they are and what they do. For now, let's just note
that this one means: "all of the prerequisites", which is all of our object
files.

The second rule is an *implicit* rule. The GNU make utility is smart enough
to know that, just from the name of rule (all of our object files), we want
to compile the associated source files of the same name seperatly. And so it
does, saving us the trouble of writing a rule for all of our object files.

### Phony targets

At the end of the make file is the `clean` rule. This rule is used to clean
the directory of binaries and other files generated when compiling. The
`.PHONY` tells make that `clean` is not a file, just the name of the rule,
which avoids confusion if we were to name a file `clean` in our directory.

