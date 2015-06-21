% ---------------------------------------------------------------------
% EG author guidelines plus sample file for EG publication using LaTeX2e input
% D.Fellner, v1.17, Sep 23, 2010


\title {CellVIEW: Illustrative Multi-scale Rendering of Large Biomolecular Datasets}

% for anonymous conference submission please enter your SUBMISSION ID
% instead of the author's name (and leave the affiliation blank) !!
\author {007}

% ------------------------------------------------------------------------

% if the Editors-in-Chief have given you the data, you may uncomment
% the following five lines and insert it here
%
% \volume{27}   % the volume in which the issue will be published;
% \issue{1}     % the issue number of the publication
% \pStartPage{1}      % set starting page


%-------------------------------------------------------------------------
\begin{document}

\teaser{
\includegraphics[width=\linewidth]{Figures/teaser}
\centering
\caption{Real-time screen-shot from our application, the view represents an illustrative cross-section of the HIV virus surrounded by blood plasma. 
Our rendering tool is directlty integrated in the Unity3D game engine and is able to render datasets with up to 30 billions at more than 30 fps in HD.}
\label{fig:teaser}
}

\maketitle

\begin{abstract}

   Pork chop doner chicken, tail shankle t-bone tri-tip. Ground round jowl pork beef, short loin tail hamburger shoulder shankle tri-tip. 
   Cow cupim ribeye bacon pancetta landjaeger prosciutto.
   Pork belly cow tongue corned beef pastrami venison spare ribs frankfurter t-bone. 
   Pig sirloin beef ribs, biltong meatball alcatra short loin shank sausage hamburger tail cow pork loin jowl tri-tip.
   Pork chop salami pig, tri-tip ground round boudin shankle tail leberkas filet mignon.

\begin{classification} % according to http://www.acm.org/class/1998/
\CCScat{Computer Graphics}{I.3.3}{Picture/Image Generation}{Line and curve generation}
\end{classification}

\end{abstract}




%-------------------------------------------------------------------------
\section{Introduction}

%In visualization sciences, datasets are constantly increasing in size and complexity, calling for new methods that could handle the large quantity of information to display.
Computational biology already offers the means to generate large and static models of cell biology, such as viruses or entire cells on the atomic level \cite{johnson2015cellpack}.
However biologists are struggling with the viewing of these large scale datasets because the tools they are usually accustomed to cannot achieve interactive frame-rates for such heavy data loads.
Foreseeing the future increase of the size of their datasets, they would need the ability to quickly render billions of atoms, while the current state-of-the-art tools are only able to interactively render up to hundreds of millions of atoms on commodity hardware \cite{grottel2015megamol}.
The interactive visualization of such interesting datasets has even greater potential than strict science-driven data exploration and could serve educational purposes too by interactively showcasing the machinery of life to a lay audience for instance.

CellVIEW is a new tool that provides fast rendering of very large biomolecular scenes and which is inspired by the state-of-the-art techniques.
By introducing new means to efficiently reduce the amount of processed geometries we manage to obtain a considerable speed-up compared to related works jumping from 10 fps up to 60 fps for similar sized datasets.
As a consequence to such optimisations the visualization results in an overwhelming number of displayed molecules which may exhibit strong visual clutter due to the complexity of their shapes.
Scientific illustrator David Goodsell has specialized in depictions of complex biomolecular sceneries. 
The goal of these paintings is to visually communicate machineries of life, and therefore they should provide a maximum degree of understanding and clarity. 
In most of his painting we observe a high degree of abstraction in the shapes of molecules (see Figure \ref{fig:David-S}).
There is an obvious logical reasoning behind this decision which goes beyond simple aesthetics and which is to reduce the level of visual clutter in the scene in order to let the viewer appreciate what is truely shown.
Inspired from the work of illustrators we designed a level-of-detail scheme which is twofold: to speed up rendering times and to clarify the scene with simpler shapes, thus procedurally imitating the mindset of scientific illustrators.

Related works have already presented bleeding-edge techniques that can render large datasets with up to billions of atoms at interactive framerates on commodity graphics hardware \cite{lindow2012interactive}\cite{falk2013atomistic}\cite{le2014illustrative}.
However, to our knowledge, the tools which implemented these techniques were either not publicly available or they remained in the prototyping stage.
Indeed, a very cumbersome task for researchers is to release of the source code once the article has been published.
Presented techniques are often just a proof-of-concept that would require additional software development to ensure a maximum degree of portability.
Unfortunately this part is often omitted because of a busy research schedule and is simply left in the hand of interested third party developers.
Consequently, if this task remains unachieved, end-users will unlikely be able to use state-of-the-art techniques in their work.
  
CellVIEW provides a direct connection between state-of-the-art techniques and end users.
We implement our tool using a free-to-use game engine and it is therefore publicly available to anyone.
Because we utilize a game engine as development platform we are able to release and deploy our tool faster since our project only consist of a few scripts and shaders.
We are therefore released from the burden of maintaining a complex software solution and from tedious deployment constraints.
Additionally since more people in the community are getting familiar with these engines we ensure a maximum level of reproducibility among other researcher too, thus breaking the barriers caused by heterogeneous toolset usage across research departments.

We showcase our tool with real large-scale scientific data such as the HIV virus or Mycoplasma cells and which has been provided to us by the domain experts.
Additionally we also extend our method to generate large strands of nucleic acids on-the-fly thus reducing the modelling effort as well as GPU transfer times and memory space.

%-------------------------------------------------------------------------
\section{Related Work}

\begin{figure}
\centering
\includegraphics[width=\linewidth]{Figures/Untitled}
\caption{An illustration of David Goodsell depicting a cross section of a Mitochondrion. Given the complexity of the scene the artist deliberately chose to render molecules with highly abstracted shapes.}
\label{fig:David-S}
\end{figure}


\begin{figure*}
\centering
\includegraphics[width=0.9\linewidth]{Figures/Picture7}
\caption{}
\label{fig:Picture7}
\end{figure*}
\textbf{Large-scale Molecular Visualization} Lindow et al. \cite{lindow2012interactive} have first introduced a method capable of fast rendering of large-scale atomic data up to several billions of atoms on commodity hardware.
Rather than transferring the data from CPU to GPU every frame they store the structure of each type of molecule only once and utilize instancing to repeat these structures in the scene.
For each type of protein a 3D grid structure containing the atoms positions is created and then stored on the GPU memory.
Upon the rendering, the bounding boxes of the instances are drawn and individually raycasted similarly to volumetric billboards \cite{decaudin2009volumetric}.
Subsequently Falk et al. \cite{falk2013atomistic} presented a similar approach with improved depth culling and hierarchical ray casting for impostors that are located far away and do not require a full grid traversal.
Although this implementation features depth culling, their method only operates on the fragment level, while they could have probably benefited from a culling on the instance level too. 
With their new improvement they managed to obtain 3.6 fps in full HD resolution for 25 billions of atoms on a NVidia GTX 580 while Lindow et al. managed to get around 3 fps for 10 billions atoms in HD resolution on a NVIDIA GTX 285. 
Le Muzic et al \cite{le2014illustrative}, introduced another technique for fast rendering of large particle-based datasets using the GPU rasterization pipeline instead.
They were able to render up to 30 billions of atoms at 10 fps in full HD resolution on a NVidia GTX Titan.
They utilize tessellation shaders to inject atoms on-the-fly in the GPU pipeline similarly to the technique of Lampe et al. \cite{lampe2007two}.
In order to increase the rendering speed they dynamically reduce the number of injected atoms accordingly to the camera depth.
To simplify the molecular structures they discard atoms uniformly along the protein chain and increase the radius of remaining atoms to compensate the volume loss.
This level-of-detail scheme offers decent results for low degrees of simplification but it does not truly guarantee to preserve the overall shape of molecules for highly simplified structures.

\textbf{Occlusion Culling} A key aspect when rendering large and complex scenes is efficient occlusion culling.
Grottel et al. presented a method to perform coherent occlusion culling for particle-based datasets which is closely related to Deferred Splatting \cite{guennebaud2004deferred} and relies on temporal coherency.
Their particle data is stored in a uniform grid and they operate the culling on two-levels: on the level of grid cells first, and on the atomic level afterwards.
Individual atoms are rendered via 2D depth impostors because they have a much lower vertex count than sphere meshes for the same results.
At the beginning of each frame they render an early depth pass with atoms that were visible during the previous frame.
This pass results in an incomplete depth buffer that they utilize to determine the visibility of the remaining particles.
When rendering a lot of primitives the graphics hardware usually takes care of discarding fragments before hand if a fragment is hidden behind an occluding geometry.
However this feature is disabled if the fragment output depth is modified, which is the case with sphere impostors.
Therefore they only render flat impostors instead to accelerate the process.
For the coarse-level culling they determine the visibility of the grid cells by testing their bounding boxes against the incomplete depth buffer via hardware occlusion queries (HOQ).
For the fine-level culling they test the visibility of individual atoms in the final render using the well known hierarchical z-buffer (HZB) visibility technique \cite{greene1993hierarchical}.
They construct the HZB from the incomplete depth buffer before hand and during the final render they discard fragment operations from the vertex shader if the visibility test fails, thus compensating for the lack of early fragment rejection with depth impostors.

\textbf{Illustrative Molecular Visualization} When rendering large structures the speed of execution is not the only concern.
As the structures increase in size they are also increasing in complexity an it is necessary to display the data in the most suitable way.
Ambient occlusion for instance has shown to be play essential role when dealing with large molecular structures as it provides important depth cues which are increasing shape perception \cite{grottel2012object} \cite{eichelbaum2013pointao}.
But the rendering style is not the only means to define visual encoding and geometric modification may be applied too.
Parulek et al.\cite{parulek2014continuous}, demonstrated a continuous level-of-detail scheme for molecular data.
Their object-space approach offers detail-on-demand in the focus area while applying gradual shape simplification schemes elsewhere.
On the finest level of detail they were showcasing SES surface representation and abstracted molecular shape of the furtherest level.
They introduced an interesting abstraction approach, other than molecular surfaces, based union of spheres obtained via clustering methods.
Several common clustering methods are evaluated and those that preserve elegantly the low-level shape details are highlighted.
The continuous level-of-detail was only demonstrated on large molecules, and has not been extended to large multi-molecular scenes.
This work is an attempt to extend the continuous level-of-detail to larger scales. %thus enabling illustrative visualization of large scenes that resemble artistic style of illustrations made by David Goodsell.

\textbf{Modelling of Nucleic Acids Chains} DNA play an utturely important role in cell biology and is an important part of our datasets too.
Therefore as with protein data we must also provide efficient rendering methods for this type of structure.
There are several scientific modeling tools \cite{macke1998modeling} \cite{lu20083dna} available that are able to generate DNA strands from a simple set of control points.
More recently Hornus et al. \cite{hornus2013easy} introduced GraphiteLifeExplorer, a DNA modelling tool especially designed for user input driven modeling of static DNA strands.
Their approach is aiming at artistic composition of 3D scene and is therefore less accurate but also faster than other methods.
Via user input and manual Bezier curves editing tools they manage to recreate DNA strands and to export it in standard molecular structure format.
The computation of the individual DNA bases is done interactively on the CPU.
The resulting data, e.g., the position and rotation of the DNA bases are uploaded on the GPU for fast rendering. 
Foreseeing the need to render large dynamic DNA strands, this approach would be likely to perform poorly because of costly transfer times between CPU and GPU.
Therefore we introduced a new GPU-based approach which relies on dynamics instancing of DNA bases along a curve.
Additionally this technique is saving a fairly large amount of precious GPU memory too, since only the control points must be stored instead of the entire chain of nucleic acids.
This approach is somehow similar to the work of Lampe et al.\cite{lampe2007two}, who used geometry shaders to dynamically instantiate ligands along the protein backbone.
The major difference here is the introduction of procedural building rules based on scientific data and the use of tessellation shaders instead which offer a much greater bandwidth of injected primitives.

\textbf{Game Engines and Biomolecular Visualization} Game engines are becoming increasingly popular in the visualization community.
Researcher have been seduced by their universal dimension and their ease of use, both in programming and deployment.
In the domain of biomolecular visualization a few articles are highlighting the fact that they have used a game engine to develop their applications. 
Shepherd et al. \cite{shepherd2014exploring} have developed a viewer to interactively view 3D genome data.
Their visualization is multi-scale and is able to render a large amount of data thanks to the implementation of a level-of-detail scheme.
Various works on interactive illustration of biological processes have also reported using game engines to visualize polymerization \cite{kolesar2014illustrating} and membrane crossing \cite{pacificvis15illustrative} in 3D and in real-time.
%The idea of developing a tool for molecular visualization with a game engine is not novel.
Similarly to our work, Baaden et al.\cite{lv2013game} developed a molecular viewer which offers artistic and illustrative rendering methods based on the Unity3D game engine.
There primary intention was to democratize biomolecular visualization thanks to the use of a more intuitive and user friendly framework.
Their tool, although just a proof-of-concept have managed to prove that game engines are also capable to foster serious visualization projects.  
A noticeable difference between CellVIEW and UnityMol, is that our tool is fully integrated in the "What you see is what you get" (WYSIWYG) editor of the Unity3D engine.
Thus our tool coexist with the engine toolset which provides us a nice set of perks which we can directly use to enhance the quality of our visualization.

%-------------------------------------------------------------------------
\section{Efficient Occlusion Culling}

The overwhelming size of the datasets that we are trying to render is calling for efficient means to perform occlusion culling.
The presented method is closely related to the two-level occlusion culling introduced by Grottel et al.\cite{grottel2010coherent} which was itself inspired from the Deffered Splating method \cite{guennebaud2004deferred}.
We have revisited those methods to provide efficient occlusion culling for biomolecular datasets that are several orders of magnitude larger.
Our rendering pipeline is based on the work of Le Muzic et al. \cite{le2014illustrative} which is designed for the rendering of large number of molecules.
This method relies on the tessellation shaders to dynamically injecting sphere primitives in the pipeline for each molecule. 

The heaviest part of the computation for this method is the geometry processing which is performed by the dynamic tessellation.
In order to lighten the processing load Le Muzic et al. suggested to reduce the number to injected atoms according to the camera depth.
However without proper occlusion culling this computation would still be performed even if a molecule is completely occluded.
We use temporal coherency to determine hidden molecules at a given frame.
To make sure that only visible geometries are sent the renderer we use a dynamic-sized render commands buffer which is recomputed before each rendering operation.
An overview of the required steps of our method is given in Figure \ref{fig:Picture7} and the steps are layed down as follow: \\

\begin{enumerate}
\item Draw visible molecules at frame t - 1
\item Generate N-Buffers  
\item Compute visibility for remaining molecules 
\item Draw remaining visible molecules
\item Read visibility from item buffer
\item Fetch colors from item buffer
\end{enumerate}
\subsection{Render Commands}

%Information relative th the individual molecules such as position, rotation, type and others is stored in large static buffer directly on the GPU.
%Additionally we also store of boolean flag on the in the same way and which is used to determine the visibility of a molecule.
Our pipeline is designed so that the visibility of a molecule is already known prior to the rendering.
A naive approach to discard hidden molecules would be to do it in the early stages of the rendering in the vertex shader, prior to dynamic tessellation. 
However discarding elements in the vertex shader would cause unnecessary processing overhead.
We use render commands instead to ensure that only visible molecules will be sent to the render.
The render commands are recomputed before every render operation.
For every visible molecule we issue and render command entry to the buffer via stream output.
The resulting the size of the commands buffer therefore matches the number of visible molecules.
Each buffer entry simply contains the id of the molecule which serves during the rendering as an index to fetch the needed information about the molecule such as position, rotation, type and also to fetch corresponding atoms for the dynamic tessellation. 

\subsection{Temporal coherency}

The key to our culling method is the use of temporal coherency to determine hidden molecules.
Upon the rendering we generate an item buffer texture which contains the id of the visible molecules instead of the color.
We process this texture and the end of each frame in order to determine the visible molecules.
These molecule are then drawn at the beginning of the next frame, by issuing one render command per visible molecule.

The resulting depth buffer is then used to query the visibility of the remaining molecules.
Grottel at al. were using HOQ to for this task, in our case when dealing with several millions of proteins the GPU driver overhead caused by HOQ would very likely cause a severe bottle neck in our pipeline.
We implemented an occlusion culling technique named N-Buffers \cite{decoret2005n} instead and which is a variant of the well known hierarchical z-buffer (HZB) culling method \cite{greene1993hierarchical}. 
A great advantage of the N-Buffers technique over traditional HZB is that it can be used with arbitrarily sized depth buffer.
Therefore we may reuse intuitively the results of the first render pass which we got by drawing visible elements at frame t-1.

\subsection{Conservative Depth Output}

\begin{figure}
\centering
\includegraphics[width=0.4\linewidth]{Figures/Picture5}
\caption{Depth conservative sphere impostors, in order to benefit from early depth culling for depth impostors we must guaranty that the output depth will be greater than the depth of the billboard as deciped in this figure.}
\label{fig:Picture5}
\end{figure}

A limitation that was stated in the implementation of Grottel et al. was the lack of early depth rejection for depth impostors.
%For this reason they precomputed an extra depth pass with flat impostors instead, which means that visible elements from frame t-1 must be rendered twice.
%Unfortunately, given the high level of complexity in our scenes the computation of an extra depth pass would likely cause unwanted overhead.
%Therefore the early depth pass which we initially render for temporal coherency culling also performs an actual render pass to which is then reused afterwards in the second pass when drawing the remaining of the visible molecules.
Thanks to advances in graphics hardware however, it is now possible to activate early depth rejection when a fragment is modifying the output depth value.
Once activated, in order for conservative depth output to work we must output a depth which is greater than the depth of the 2D billboard.
This way the GPU is able to tell if a fragment will be visible before hand by querying the visibility of the fragment internally. 
A description of the depth conservative output sphere impostor is given in Figure X.
Additionally, to limit the bandwidth due to the large number of texture write we only output the id of the molecules upon rendering.
The colors are fetched afterwards in postprocessing by reading the molecules properties from the id.
We have seen very little overhead when drawing sphere impostors with id + convervative depth compared to flat depth impostor with no colors.


%When rendering the early depth pass Grottel et al. were also disabling other type of output such as id and color to speed up the rendering.
%In our case since we wish to reuse this pass later we must also output the fragment information as normally.
%To limit the bandwidth due to the large number of texture write we only output the id of the molecules.


%-------------------------------------------------------------------------
\section{Twofold Level-of-Detail}
\label{sec:biomol}

\begin{figure}
\centering
\includegraphics[width=0.8\linewidth]{Figures/Picture4}
\caption{Our level-of-detail scheme allow to greatly reduce the number of sphere primitives. In the upper-left corner the protein is show with full-atomic detail, in the upper-right corner the molecule is drawn with only 15 percent of the overall sphere count, lower-right is 5 percent and lower-left 0.5 percent reducing the number of spheres from 10182 to 50 while preserving the overall shape of the protein.}
\label{fig:Picture4}
\end{figure}

Proteins are key elements of biological organisms and thus it is important to visualize them in order to understand how those machineries work.
They are also present in fairly large quantities which is challenging to render interactively without proper level-of-detail schemes.
Additionally their complex shapes might cause a high degree of visual clutter which may be render unpleasant results.

We propose a twofold level-of-detail scheme which provides rendering acceleration and offers and clearer depiction of the scene using smoothly abstracted shapes.
Our technique also offers a seamless continuum between the different levels of abstractions.
%To simplify molecular structures Le Muzic et al. \cite{le2014illustrative} were discarding atoms uniformly along the backbone of the protein while the radius of remaining atoms was increased in order to compensate the voids.
%Because this approach does not guaranty the overall volume of the molecule to be preserved it may exhibits incoherent shapes with high degree of simplification.
We employ clustering methods, similarly to the technique of Parulek et al. \cite{parulek2014continuous} to simplify the shape of the molecules and reduce the amount of primitives to render.
Clustering offers a very good decimation ratio as well as accurate shape abstraction because they tend to preserve low-frequency details.
With higher shape accuracy we are also able to switch to simpler LOD proxies closer to the camera thus gaining render speed without compromising image quality.
The clusters spheres are computed on the CPU and then stored in large GPU buffers that may be accessed by the dynamic tessellation via address pointers similarly to atom spheres.
We empirically determined that four levels of details where sufficient with our current dataset.
With these settings we also payed a special attention not to compromise image quality.
All the proteins share the same level proprieties, the first level includes 100 percent of the atoms, the second level has a decimation ratio of around 15 percent, the third level 5 percent and the last level down to 0.5 percent.

The first two levels were computed with a simple method based on spatial coherency of atoms along the protein chain, also known as coarse grain molecular simplification.
This method has previously been used in biomolecular visualization to simplify the generation of molecular surfaces \cite{krone2009interactive}. 
We use this approach because it is faster to compute than standard clustering method for similar results.
For the last level we wanted to dramatically reduce the number of spheres and therefore the previous approach, would not perform well enough for this task.
We use k-means clustering for this task.
A major issue common to many clustering algorithms is the slow computing speed when dealing with several thousands of spheres.
We reuse the results of the third clustering level as input thus decreasing dramatically computation times.
The resulting levels are shown on figure \ref{fig:Picture4}.

When observing the large-scale biomolecular depictions of David Goodsell we noticed that molecules tend to increase in volume with the distance.
This operation is probably done to compensate the relatively small size of proteins when viewed in their natural embedding.
We subjectively found this artistic choice to be visually pleasant and relevant too.
Therefore we also include a scaling factor to our illustrative level-of-detail.
Each LOD level has a proper range in terms of camera depth which is common to every type of molecule, i.e., level 0 is defined between distance 0 and 50 A, level 2 between 50 and 100 A, etc.
We define min and max radius for each range and we smoothly interpolate between these values.
Results of our twofold LOD can be seen in the supplementary video material.

%Show comparison between No LOD and LOD

%-------------------------------------------------------------------------
\section{Dynamic DNA Generation}

\begin{figure*}
\centering
\includegraphics[width=1\linewidth]{Figures/Picture3}
\caption{}
\label{fig:Picture3}
\end{figure*}

Animating individual molecules is fairly straightforward because modifying the atomic structure may not required.
In the case of DNA the positions of the control points of the DNA path are highly influencing its structure, namely the positions and rotations of the individual nucleic acids.
As a result each modification of the control points of the DNA path would require a new computation of the strand.
Current approaches are only performed on the CPU \cite{hornus2013easy} \cite{lu20083dna} \cite{macke1998modeling} which means that the whole nucleic acids chain has to be transferred to the GPU upon re-computation.
While this approach is viable for low to mid sized DNA strands it is very likely to perform poorly for large and dynamic DNA paths featuring a large number of control points.

We propose to use the dynamic tessellation to leverage the generation of nucleic acids strands.
So far we only used tessellation to instantiate data priorly stored on the GPU memory.
However it would be rather trivial to include building rules that are proper to DNA modeling to procedurally generate a double helix structure simply based control points.
Thus, the data transfers to the GPU would be dramatically reduced as well a GPU memory space.

Similarly to GraphiteLifeExplorer \cite{hornus2013easy}, our goal is more illustrative that strict biomolecular modeling therefore we are privileging render speeds over accuracy and we provide only a limited array of folding types.
Although the study of DNA structures have revealed many different types of foldings requiring complex modeling algorithms, the most commonly recognizable shape is the B-DNA and exhibits a regular structure which is simple to model: a spacing of 3.4 A and a rotation of 34.3 degrees between each base.
Based on these rules we are able to dynamically generate B-DNA strands on the GPU via dynamic tessellation.
The workflow which we employ is described as follow:

\begin{enumerate}
\item Do control points resampling (on the CPU).
\item Compute smooth control points normals (on the CPU).
\item Upload control points data to the GPU 
\item Draw all the path segments in one pass, one vertex shader per segment
\item Read the control points and adjacent points needed for smooth cubic interpolation. (In vertex shader, for each segment)
\item Do uniform sampling along the cubic curve segment to determine the positions of the bases. (In vertex shader, for each segment)
\item Pass the position of the bases to the tessellation shader. (In vertex shader, for each segment)
\item Compute normal vector of the base using linear interpolation between the control points normals (In tessellation shader, for each base)
\item Inject atom then translate and rotates accordingly (In tessellation shader, for each atom of each base)
\item Render sphere impostor from injected atom (In geometry \& fragment shader, for each atom of each base)
\end{enumerate}

\subsection{Smooth Normals Computation}
A well know challenge when dealing with 3D splines is to determine smooth and continuous frames along the whole curve.
Any twists or abrupt variation in frame orientation would cause visible artefacts due to irregularities in the DNA structure which we should avoid at all costs.  
We perform the computation of the smooth and continuous primarily on the CPU.
We first determine the normal direction for every control points of the path.
Then we browse the control points in serial and we rotate the normal direction vector around the tangent vector in order to minimize the variation in orientation compared to the previous control point normal.
The recalculated normals are then uploaded to the GPU along with the control points positions. %, and during the instantiation of the nucleic acids we obtain the normal vector of a nucleic acid by linear interpolation of the two segment normal vectors.
The pseudo code for computing the minimized rotation normal vectors is given in appendix X.

\subsection{Double Helix Instancing}
When instancing individual pairs of nucleic acids in the tessellation shader, we first fetch the nucleic acid atoms, position them along the curve, orient them toward the normal direction and then rotate then around the tangent vector in order the generate the double helix.
We always orientate the first base of a segment according to the normal direction only, while the subsequent bases are all oriented toward the normal direction first and then rotated with an increasing angular offset of 34.3 degree around to the tangent of the curve.
The angular offset of a given base is defined as follow: $ \alpha = i \times 34.3$, where i corresponds to the index of the base inside a segment.
The last base of a segment must therefore always perform an offset rotation of $ \alpha = 360 - 34.3$ degrees around the tangent so that it connects smoothly to the first base of the next segment which is oriented towards the normal vector only. 
The result of the procedural generation of B-DNA is given in Figure \ref{fig:Picture3} as well as a visual explanation of the different steps.

\subsection{Control Points Resampling}
Given the fact that the bases of a segment must perform a revolution to connect smoothly to the next segment it is trivial to determine the number of bases per segments as follow: $n = 360 \div 34,3 $.
From the number of bases per segment we can easily deduce the required size of segment as follow: $ s = n \times 3.4A$, which results in a segment length of 35 A approximatively.
This constraint implies all the control points to be spaced uniformly with a distance of 35A.
However it may be the case that control points obtained via modelling software have arbitrary spacing.
Therefore we must re-sample the control points along the curve to ensure a uniform spacing before uploading it to the GPU.
Although we resample the control points accordingly to the B-DNA build rules, the length of the interpolated curve segments will always be slightly greater because of the curvature.
However we did not find this to be visually disturbing, probably because consecutive segments in our dataset did not showcase critically acute angles so the overall curvature of the path remained rather low. 

%-------------------------------------------------------------------------
\section{Perks and Limitations of a Game Engine}

Although game engines may not yet be the perfect all-in-one solution they are a good contenders to generic visualization framework nevertheless.
Above all, they offer ease of access to GPU features for fast computation, which is critical for high performance computing, while remaining user friendly. 
CellVIEw is implemented in Unity3D one of the most popular game engine which uses C\# as a scripting languages and also supports a large array of platforms from desktop PCs to mobile devices.
It is worth mentioning that the Unity3D engine is free of charge for the personal edition and thus is accessible to anyone.
In the section we briefly review the perks and limitation of such engine when used a development platform for scientific visualization.

\subsection{What We Liked}

\textbf{Scripting} The language which is used for coding with Unity3D is C\# while the engine is internally coded in C++.
The simplicity of C\# makes it a great language for quick prototyping over C++, aditionnally C\# is more accessible to enthusiasts programmers than C++.
Therefore the use of scripting languages contribute to making our tools more universal and accessible.
Additionally the deployment of our tool is made a lot more easier since our project only consists of few scripts while the heavy software part is actually located in the engine.

\textbf{Editor} The game engine features a WYSIWYG editor which is a great tool for artistic setup because it offers a real-time preview of the application.
And thanks to the hot-reload any code changes are automatically recompiled in the background so we do not have to shut down the editor after each modification. 
The editor also features UI extension capabilities which we use to design the custom UI of CellVIEW.

\textbf{Mesh-based Rendering} While our datasets are made out of particles, cell biology offers different types of data acquisitions which may results in surface representation for instance.
Therefore we designed our rendering pipeline to coxexists with the legacy mesh pipeline of the engine.
Hence we may use meshes that are either artist-designed or obtained via data acquisition and render them easily together with our own data in the same view.

\textbf{High-End GPU Capabilities} With Unity3D most of the low-level graphics API is exposed to the scripting world.
Therefore we had no difficulty at all to implement our custom pipeline which relies on advanced graphics features such as tesselation or compute shaders.
Comparing to native C++ graphics development we even found it to be easier to code GPU algorithm because we did not have to pay much attention on the CPU setup and could focus more on doing actual shader programming.

\textbf{Maintenance} Unity3D is a very popular framework which generate large revenues in the game industry. 
Therefore teams of professional developers are constantly working on improving the tool and  supporting bleeding edge features.

\textbf{Community} Unity3D is a universal tool that is widely use by many independent developers and professional multi-disciplinary teams.
Therefore the community is very large, and in addition to a very dense online documentation it is very easy to seek for help online when facing problems with the engine.

\textbf{Deployment} Although the editor is already a very good tool to work with, we may still want to export the program in a standalone application for deployment.
From our experience the building process and deployment is always a very cumbersome task, with Unity3D, the process of compiling a program to an actual executable file is only a matter of a few clicks.

\textbf{Miscellaneous} The engine has a large array of features which we could use straight out-of-the-box.
One feature which we use extensively in CellVIEW are image post-processing effects, such as ambient occlusion, depth-of-field or motion blur.
Such features are always cumbersome to re-implement from scratch but thanks to the engine we have access to professional real-time effect with no additional efforts.
Many other features could also be valuable such as efficient real-time physics for instance.

\subsection{What We Did Not Like}

\textbf{CPU Performances} While GPU performance is not dependent of the employed framework, CPU performance might be strongly affected with the use of a C\# scripting engine compared to native C++.
While the modern C\#/.NET framework is doing considerable effort towards mutli-platform and close to native performance, Unity3D still features scripting engine which is largely out of date and this is why we would not recommend it for heavy CPU computation.
It is possible though to use ad-hoc natively compiled libraries or plugins in case CPU performance is absolutely critical but it is not an elegant out-of-the-box solution which has limitations and require additional work.
Unity3D has made this issue a priority in their development road-map so we have good hopes to see improvement on this side in the next iteractions of the framework.

\textbf{GPU Performance and Portability} While Unity3D has made cross-plarform compilation one its major advantages, to this day, high-end graphics capabilities are only available with DirectX 11.
Thus we may only deploy CellView to machines that supports DirectX 11 which excludes tablets, Linux and OSX machines.
However, Unity3D recently announced that it will soon extend high-end graphics capabilities to support modern OpenGL, and will even provide support for compute and tessellation to mobile devices.

\textbf{Source Code Availability} Game engines such a the Unreal Engine have recently released their source code to the public, in order to encourage third party and community-based extensions of the engine.
In the case of Unity3D the source code of the engine is still not available, which means that if a critical feature is missing in the core of the engine there will be no other option but requesting it rather than simply coding the feature ourself.
This is a very frustrating aspect of the engine we are using right now and we hope to see changes in that regard in the future. 

%-------------------------------------------------------------------------
\section{Results}

We have tested our techniques with two different datasets which result from the same modeling software.
The data was obtained with CellPACK \cite{johnson2015cellpack}, a modeling tool for procedural generation of large biomolecular structures.
Based on real scientific data such as concentration and spatial distribution they managed to generate a whole model of the HIV virus via a packing method based on collisions constraints. 
They also compare their results with fluorescence microscopy images of real organisms to validate their results.

Our program read the files that are generated by the tool and is able to reconstruct the scene in a multiscale approach.
The generated files comprise a list of elements, namely the name, position, rotation and PDB identifier \cite{sussman1998protein}.
The structural data is directly fetched online from the Protein Database, in case an entry is not present in the database we load the protein information from a dedicated repository provided by the domain experts.
The generated files also include control points for the linear type of structures such as DNA, RNA or lypoglycane.
The data that we is showcasing are particularly interesting to use because we scenery we are depicting are actually scientifically accurate.

\subsection{Use cases}

The first dataset we are showcasing is the HIV virus surrounded by blood plasma.
The dataset comprise a total number of 70 millions atoms and 40 different species of molecules. 
For the purpose of rendering benchmarks we duplicate this dataset 75 times to reach a total number 30 billions of atom, which is a similar size of dataset that was showcased by Le Muzic et al.
The rendering test was performed on an  Intel Core i7-3930 CPU 3.20 GHz machine coupled with a GeForce GTX Titan X graphics card with 12GB of video RAM.
We additionally provide a descriptive table (see Table X) for the average duration of the rendering steps which we describe in Figure \ref{fig:Picture7}.
Because of the culling mechanisms the load of visible molecules and thus the frame-rate varies according to the viewpoint.
On average we did not see the framerate dropping below 30 fps when using an accurate type of occlusion culling, and this was increased up to 60 fps when using a fast and lower quality type of culling. 
When zooming far out in order to see the dataset as a whole, the view starts to exhibits graining aliasing artifacts due to the very small size of individual molecules.
While image quality could be improved with anti-alisaing techniques the issue would still persist for larger zooming scale.
What is truly needed here is a new type of abstraction for this data to be shown at such scale that would decrease visual clutter and increase clarity and understanding.

The HIV virus only contains RNA which is similar do DNA, but features much more complex modeling rules that DNA which forbids dynamic procedural generation.
For this specific case the RNA atomic structure would have to modelled ad-hoc with a third party tool before being loaded in CellVIEW.
We demonstrate the use of our dynamic building rules with the DNA data of Mycoplasma a very small bacteria which has been widely studied by biologists.
For this dataset we are only showcasing the DNA data as it is still a work in progress.
The DNA comprise a set of control points and well as the PDB reference to the nucleic acids and is loaded directly from the files generated by CellPACK.
The data we showed was made out of XX control points of an overall number of XX atoms, and the results can be seen in Figure X.

\subsection{Discussion}

From discussions with domain experts we got positive response.
So far the viewing of their data was rather cumbersome and they now have the possibility to use state-of-the-art technique is their work.
They regretted the fact that it was not directly implemented in their homemade toolset but they also had experience working with the Unity framework so the transition was rather smooth.
A feature that has been frequently requested was also the ability to render the scene imitating fluorescent microscopy images.
This type of representation is very useful to them to compare and validate results with real microscopy images.
So was the generation of such images was very cumbersome and thanks to this small addition we did they are now able to generate such microscopy images in real-time side by side with 3D multi-scale representation.

%-------------------------------------------------------------------------
\section{Conclusions and Future Work}

We have introduced CellVIEW a tool for real-time multiscale visualization of large molecular landscapes.
Our tool is able to load files generated by CellPACK a powerful modeling tool for designing entire organisms on the atomic level.
CellVIEW was engineered to work seamlessly inside the Unity game engine, which allow use to prototype and deploy faster without compromising GPU performance.
The method which we presented also feature considerable improvement over previous work.
We provide the mean for efficient occlusion culling which is crucial when dealing with such large scale datasets.
We also designed a level-of-detail which allow to both speed up rendering times and provides a clear and accurate depiction of the scene.
Finally we demonstrated the use of dynamic tessellation to generate biolmolecular structures on-the-fly based on scientific modeling rules.

In future work we would like to tighten the collaboration with domain experts and achieve interactive viewing of entire and more complex organisms and bacteria such as E.Coli for instance.
As the size of the data and the scale both increase the view exhibits highly grained results due to the very small size of molecules, in the future we would like to focus on better representation for this case, and perhaps find new semantics that could be integrated in our level-of-detail continuum.
We also would like to use our rendering to experiment with in-situ simulations as a visual exploration tool for scientists but also as education tool to showcase the machinery of life to a law audience.


%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{egbibsample}
\end{document}
