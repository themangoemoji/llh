# Local Link Hash 
###### Make writing down URLs *really* easy

Local Link Hash is a tool I developed to help myself with my note taking and to-do lists. I love paper, but it can be tricky for me juggle keeping track of all the links I have to come back to. With **Local Link Hash** (LLH), I found a way to easily write down a link associated with a task without having to bookmark anything or use an online notetaking tool.

## How it works
I want to apply for GitHub's Application Engineer position when I get home. I find the link to the posting at:
https://jobs.lever.co/github/83e67f41-64c5-46f0-9a3d-ae0066692546
Well, if I write this down in my planner it's going to take me a good bit. I could bookmark it, but I don't use bookmarks and then I'd want to write down where I put it in my bookmark manager... you get the idea. I like paper. LLH can solve this!

```
$ LLH
$ Input URL or existing LLH: https://jobs.lever.co/github/83e67f41-64c5-46f0-9a3d-ae0066692546
$ 'https://jobs.lever.co/github/83e67f41-64c5-46f0-9a3d-ae0066692546' --> abk
$ Value copied to clipboard.
```

Cool. We just linked `abk` to that link, and if you need it, `abk` was also copied to the clipboard. 
Now I can write this in my planner.

> * Fill out GitHub app tonight! --> **abk**

And tonight when I get home, I'll use LLH to get my life in order!

```
$ LLH
$ Input URL or existing LLH: abk
$ 'abk' --> https://jobs.lever.co/github/83e67f41-64c5-46f0-9a3d-ae0066692546
$ Value copied to clipboard.
```

With URL-foo like that I'm bound to land the job.

## Future Directions
* Putting LLH in the cloud to make links persistent between devices
* Android App in developments
* iOS
