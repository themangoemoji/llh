# Local Link Hash (LLH)
###### Make writing down URLs *really* easy

Local Link Hash is a tool I developed to help myself with my note taking and to-do lists. I love paper, but it can be tricky for me to juggle keeping track of all the links in my life. With **Local Link Hash** (LLH), I found a way to easily write down a link associated with a task.

## What Problems Does LLH Solve?
I want to apply for GitHub's Application Engineer position when I get home. I find the link to the posting at:
https://jobs.lever.co/github/83e67f41-64c5-46f0-9a3d-ae0066692546

Well, if I write this down in my planner it's going to take me a good bit. What can I do?

* I could bookmark it, but I don't use bookmarks and then I'd want to write down where I put it in my bookmark manager. 
* I could use an online URL shortener like bit.ly that would git us a URL like http://bit.ly/1XqpsPj, but I don't need or want to share this with anyone, plus I would have to copy down at least 7 characters to remember that link because those links need to be public to everyone!
* I could use an online note taking tool and paste all of my links, but I always come back to paper notes and lists for flexibility.

You get the idea. I like paper. LLH can solve all of these problems!

## How it works

Lets take that link to the application and run it through LLH:

```
$ llh
$ Input URL or existing LLH: https://jobs.lever.co/github/83e67f41-64c5-46f0-9a3d-ae0066692546
$ 'https://jobs.lever.co/github/83e67f41-64c5-46f0-9a3d-ae0066692546' --> abk
$ Value copied to clipboard.
```

Cool. We just linked `abk` to that link, and if you need it, `abk` was also copied to the clipboard. 
Now I can write this in my planner.

> * Fill out GitHub app tonight! --> **abk**

And tonight when I get home, I'll use LLH to get my life in order!

```
$ llh
$ Input URL or existing LLH: abk
$ 'abk' --> https://jobs.lever.co/github/83e67f41-64c5-46f0-9a3d-ae0066692546
$ Value copied to clipboard.
```

With time saving URL-foo like that I'm bound to land the job.

## Future Directions
* Putting LLH in the cloud to make links persistent between devices
* Android App in developments
* iOS
