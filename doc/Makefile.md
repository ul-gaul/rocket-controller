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

### Why not use *insert modern programming langage*?

asdf

### Why not use an IDE?

asdf

## Rocket controller Makefile explanation

The Makefile used

