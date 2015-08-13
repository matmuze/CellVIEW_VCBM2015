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
\includegraphics[width=\linewidth]{Figures/P1.PNG}
\centering
\caption{Real-time screen-shot from our application, an illustrative cross-section of the HIV virus surrounded by blood plasma. Our rendering tool is directly integrated in the Unity3D game engine and is able to render datasets with up to 15 billion atoms smoothly at 60Hz and in high resolution. Because the dataset is rather complex we opted for an illustrative rendering style to improve shape perception and which was inspired by the work of scientific illustrators.}
\label{fig:teaser}
}

\maketitle
    \begin{abstract}
In this article we introduce CellVIEW, a new system to visualize in real-time large biomolecular datasets on the atomic level. Our tool is unique and has been specifically designed to match the ambitions of our domain experts to model and interactively visualize structures comprised of several billions atoms, which corresponds to sizes of small bacterial organisms. CellView have been successfully used for displaying a scene containing the entire HIV virus surrounded by Blood plasma representative molecules. This HIV scene has been duplicated 72 times leading to a total number of 30 billion atoms at interactive rate. In order to achieve interactivity, CellVIEW (i) improves state-of-the-art molecular visualization techniques by introducing an efficient and highly scalable occlusion culling scheme;
(ii) uses an illustrative approach for the rendering of these molecular landscapes inspired by the work of scientific illustrators; and (iii)
rely on a two-fold level-of-detail to accelerate the rendering and to improve shape perception. The main part of our datasets is made out of proteins, but it also comprises of nucleic acids strands which are stored as sets of control points. For that specific case, we extend our rendering method to also support the dynamic generation of DNA strands directly on the GPU. CellVIEW has been directly implemented inside a game engine to reduce software development work-load and to bring bleeding-edge graphics techniques more easily to the end-users. To our knowledge CellVIEW is the only suitable framework for atomistic visualization of large bimolecular landscapes and is also accessible to a large audience due to the use of a free-to-use popular game engine.

\begin{classification} % according to http://www.acm.org/class/1998/
\CCScat{Computer Graphics}{I.3.3}{Picture/Image Generation}{Line and curve generation}
\end{classification}

\end{abstract}


%-------------------------------------------------------------------------
\section{Introduction}

Computational and structural biology already offers the means to generate large and static models of cell biology, such as viruses or entire cells on the atomic level \cite{johnson2015hiv}\cite{johnson2015cellpack}. The interactive visualization of such interesting datasets, while very challenging, has even greater potential than strict science-driven data exploration. 
For instance, interactively showcasing the machinery of life to a lay audience could improve the understanding of basic biology, and thus serve an educational purpose.
However, biologists struggle with viewing these large scale datasets, because the tools they are usually accustomed to cannot achieve interactive frame-rates for such heavy data loads at the atomic level. Moreover, foreseeing the future increase of the size of their datasets, they would need the ability to quickly render billions of atoms. Current tools used by fields expert consist in molecular viewer (such as VMD\cite{HUMP96}, Chimera\cite{chimera}, PMV\cite{pmv}, Pymol\cite{PyMOL}, QuteMol\cite{qutemol}), plugins for advanced 3d softwares (ePMV\cite{epmv}, mMaya\cite{mmaya}, bioblender\cite{bioblender}, unityMol\cite{lv2013game}) and specialized tools (Molecular Flipbook\cite{mfbook} and GraphiteLifeExplorer\cite{hornus2013easy}). Theses tools can achieve reasonable performance for large data set, such as the HIV virus, by using simple representation (Lines or Points), or by using instance of mesh representing molecular surface. However, theses tools can't achieve the rendering at interactive frame-rates with atomic details (Van der wall or CPK spherical representation). To overcome the limitation of the state-of-the-art tools, related works have already presented bleeding-edge techniques that can render large datasets with up to billions of atoms at interactive framerates on commodity graphics hardware ( Lindow \textit{et al.} 10 billions atoms 3fps\cite{lindow2012interactive}, Le Music \textit{et al.} 30 billions atoms 10fps\cite{le2014illustrative}, Falk \textit{et al.} 25 billions atoms 3.6fps\cite{falk2013atomistic}, Grottel \textit{et al.} 100 millions spheres 10fps\cite{grottel2015megamol} and Guo \textit{et al.} ??\cite{guo2015}). However, to our knowledge, most of the tools which implemented these techniques were either not publicly available, or are difficult to access for a regular end-user. Indeed, a very cumbersome task for researchers is to release a usable version of the source code once the article has been published. Presented techniques are often just a proof-of-concept that would require additional software development to ensure a maximum degree of portability. Unfortunately, this part is often omitted because of a busy research schedule and is simply left in the hand of interested third party developers.
Consequently, if this task remains unachieved, end-users are unlikely to use state-of-the-art techniques in their work.

CellVIEW is a new tool that provides fast rendering of very large biological macromolecular scenes and is inspired by state-of-the-art techniques. CellVIEW provides a direct connection between state-of-the-art techniques and end users. CellVIEW is implemented in a free-to-use game engine, unity3D, and it is therefore publicly available to anyone. Because we utilize a game engine as development platform, we are able to release and deploy our tool faster, since our project only consist of a few scripts and shaders. We are then released from the burden of maintaining a complex software solution and from tedious deployment constraints. Additionally, since more people in the community are getting familiar with these engines, we ensure a maximum level of reproducibility among other researcher too, thus breaking the barriers caused by heterogeneous toolset usage across research departments.

CellVIEW provides fast rendering by introducing new means to efficiently reduce the amount of processed geometries. We obtain a 6 times speed-up compared to related works, jumping from 10 fps up to 60 fps for similar sized datasets. CellVIEW improve previous approaches by using (i) an optimized occluding pass using N-depth, (ii) the sphere impostor quad augmented by the tessellation shader, (iii) a batch system for large non repeating data such as lipids membrane bilayer, and (iv) a fully procedural DNA visualization from a given set of control point. As a consequence to such optimizations, the visualization results in an overwhelming number of displayed molecules which may exhibit strong visual clutter due to the complexity of their shapes. However, observing the work of David Goodsell\cite{goodcellpaint}, pioneer in the representation of cellular environment at the molecular level, gave some hint on how to overcome such difficulties. The goal of David Goodsell's paintings is to visually communicate machineries of life, and therefore they should provide a maximum degree of understanding and clarity. In most of his painting we observe a high degree of abstraction in the shapes of molecules (see Figure \ref{fig:David-S}).
There is an obvious logical reasoning behind this decision which goes beyond simple aesthetics and which is to reduce the level of visual clutter in the scene in order to let the viewer appreciate what is truly shown.
Inspired from the work of illustrators, such as David Goodsell, we designed a level-of-detail scheme which is twofold: to speed up rendering times by reducing the number of spheres to be displayed and to clarify the scene with simpler shapes, thus procedurally imitating the mindset of scientific illustrators.

We showcase our tool with large-scale scientific data of interest such as a model of the mature HIV virus\cite{johnson2015hiv} or the Mycoplasma mycoide bacteria which have been provided to us by domain experts. Theses dataset try to combine most recent structural knowledge of a particular system, and integrate it in a 3d model\cite{johnson2015cellpack}. 


%-------------------------------------------------------------------------
\section{Related Work}

\begin{figure}
\centering
\includegraphics[width=\linewidth]{Figures/P2.PNG}
\caption{An illustration of David Goodsell depicting a cross section of a Mitochondrion. Given the complexity of the scene the artist deliberately chose to render molecules with highly abstracted shapes.}
\label{fig:David-S}
\end{figure}

\textbf{Large-scale Molecular Visualization} Lindow \textit{et al.} \cite{lindow2012interactive} have first introduced a method capable of quickly rendering large-scale atomic data consisting of several billions of atoms on commodity hardware. Rather than transferring the data from CPU to GPU every frame, they store the structure of each type of molecule only once and utilize instancing to repeat these structures in the scene.
For each type of protein a 3D grid structure containing the atoms positions is created and then stored on the GPU memory.
Upon rendering, the bounding boxes of the instances are drawn and individually raycasted, similarly to volumetric billboards \cite{decaudin2009volumetric}.
Subsequently Falk \textit{et al.} \cite{falk2013atomistic} presented a similar approach with improved depth culling and hierarchical ray casting for impostors that are located far away and do not require a full grid traversal.
Although this implementation features depth culling, their method only operates on the fragment level, while they could have probably benefited from a culling on the instance level too. 
With their new improvement they managed to obtain 3.6 fps in full HD resolution for 25 billions of atoms on a NVidia GTX 580, while Lindow \textit{et al.} managed to get around 3 fps for 10 billions atoms in HD resolution on a NVIDIA GTX 285. 
Le Muzic \textit{et al.} \cite{le2014illustrative}, introduced another technique for fast rendering of large particle-based datasets using the GPU rasterization pipeline instead.
They were able to render up to 30 billions of atoms at 10 fps in full HD resolution on a NVidia GTX Titan.
They utilize tessellation shaders to inject atoms on-the-fly in the GPU pipeline similarly to the technique of Lampe \textit{et al.} \cite{lampe2007two}.
In order to increase the rendering speed they dynamically reduce the number of injected atoms accordingly to the camera depth.
To simplify the molecular structures they discard atoms uniformly along the protein chain and increase the radius of remaining atoms to compensate the volume loss.
This level-of-detail scheme offers decent results for low degrees of simplification but it does not truly guarantee to preserve the overall shape of molecules for highly simplified structures.

\textbf{Occlusion Culling} A key aspect when rendering large and complex scenes is efficient occlusion culling.
Grottel \textit{et al.}\cite{grottel2010coherent} presented a method to perform coherent occlusion culling for particle-based datasets, which is closely related to Deferred Splatting \cite{guennebaud2004deferred} and relies on temporal coherency.
Their particle data is stored in a uniform grid, and they operate the culling on two-levels: on the level of grid cells first, and on the atomic level afterwards.
Individual atoms are rendered via 2D depth impostors, because they have a much lower vertex count than sphere meshes for the same results.
At the beginning of each frame they render an early depth pass with atoms that were visible during the previous frame.
This pass results in an incomplete depth buffer that they utilize to determine the visibility of the remaining particles.
When rendering a lot of primitives, the graphics hardware usually takes care of hidden discarding fragments beforehand.
However this feature is disabled if the fragment output depth is modified, which is the case with sphere impostors.
Therefore, they only render flat impostors instead to accelerate the process.
For the coarse-level culling they determine the visibility of the grid cells by testing their bounding boxes against the incomplete depth buffer via hardware occlusion queries (HOQ).
For the fine-level culling they test the visibility of individual atoms in the final render using the well known hierarchical z-buffer (HZB) visibility technique \cite{greene1993hierarchical}.
They construct the HZB from the incomplete depth buffer beforehand, and during the final render they discard fragment operations from the vertex shader if the visibility test fails, thus compensating for the lack of early fragment rejection with depth impostors.

%cite atomsviewer culling methods as well, which use a probabilistic octree 

\textbf{Illustrative Molecular Visualization} When rendering large structures the speed of execution is not the only concern.
As the structures increase in size, they are also increasing in complexity, and it is necessary to display the data in the most suitable way.
Ambient occlusion for instance has shown to play an essential role when dealing with large molecular structures as it provides important depth cues which increase shape perception \cite{grottel2012object,eichelbaum2013pointao}.
But the rendering style is not the only means to define visual encoding, and geometric modification may be applied too.
Parulek \textit{et al.}\cite{parulek2014continuous}, demonstrated a continuous level-of-detail scheme for molecular data.
Their object-space approach offers detail-on-demand in the focus area while applying gradual shape simplification schemes elsewhere.
On the finest level of detail they were showcasing solvent excluded surface (SES) representation and abstracted molecular shape for distant molecule.
They introduced an interesting abstraction approach, other than molecular surfaces, based on union of spheres obtained via clustering methods.
Several common clustering methods are evaluated and those that preserve elegantly the low-level shape details are highlighted.
The continuous level-of-detail was only demonstrated on large molecules, and has not been extended to large multi-molecular scenes.
This work is an attempt to extend the continuous level-of-detail to larger scales. %thus enabling illustrative visualization of large scenes that resemble artistic style of illustrations made by David Goodsell.

\textbf{Modelling of Nucleic Acids Chains} DNA plays a key role in cell biology and is an important part of our datasets as well.
Therefore, as with protein data we must also provide efficient rendering methods for this type of structure.
There are several scientific modeling tools \cite{macke1998modeling,lu20083dna,hornus2013easy} available that are able to generate DNA strands from a simple set of control points. All of these approaches are performed on the CPU, which means that the bases position and
rotation must be uploaded on the GPU prior to the rendering. Because of the cost of transferring data from CPU to GPU, however, this approach would likely perform poorly when rendering and animating large DNA strands. Therefore, we
introduce a new GPU-based approach which relies on dynamic instancing of DNA bases pairs along a curve. This approach is similar to the work of Lampe \textit{et al.} [LVRH07], who use geometry shaders to dynamically instantiate residues along the protein backbone. The major difference here is the introduction of procedural building rules based on scientific data and the use of tessellation shaders instead of geometry, which offer a much greater bandwidth of injected primitives. Moreover, our approach can be extended and applied to any fiber or repetitive molecular object (Actine, Microtubule, lipoglycane, etc...) that are present in any cellular environment. This require to only change the procedural building rules and the building block.


\textbf{Game Engines and Biomolecular Visualization} Game engines are becoming increasingly popular in the visualization community.
Researcher have been seduced by their universal dimension and their ease of use, both in programming and deployment.
In the domain of biomolecular visualization a few articles highlight the fact that they have used a game engine to develop their applications. 
Shepherd \textit{et al.} \cite{shepherd2014exploring} have developed an interactive application to showcase 3D genome data.
Their visualization is multi-scale and is able to render a large amount of data thanks to the implementation of a level-of-detail scheme.
Various works on interactive illustration of biological processes have also reported using game engines to visualize polymerization \cite{kolesar2014illustrating} and membrane crossings \cite{pacificvis15illustrative}.It is also worth mentioning the Molecular Flipbook\cite{mfbook} a framework developed on top of the blender game engine. The Molecular Flipbook aim is to help scientific and illustrator to easily design, model, animate and share molecular machinery. 
Similarly to our work, Baaden \textit{et al.}\cite{lv2013game} developed a molecular viewer which offers artistic and illustrative rendering methods based on the Unity3D game engine.
Their primary intention was to democratize biomolecular visualization thanks to the use of a more intuitive and user friendly framework.
All of theses tool has managed to prove that game engines are also useful in serious visualization projects. However, they show limitation for the visualization of larger scene at a cellular scale. For instance, unityMol focus on the rendering and the exploration of one molecule at a time. The Molecular Flipbook instead provide tools to animate and design more complex scene but it is limited to schematic representation (SES, cartoon) and will not be able to handle larger scene with atomic details. We developed CellVIEW to address the problem of visualizing multi-scale scenes with atom level complexity. Moreover, one noticeable technical difference presents in CellVIEW is that our tool is fully integrated in the "What you see is what you get" (WYSIWYG) editor of the Unity3D engine.
Thus our tool coexists with the engine toolset which provides a rich set of functionalities which we can directly use to enhance the quality of our visualization (e.g. Depth of fields, Image effect, Ambiant occlusion, etc...).

%we can also do a table comparison here. Theses software are available.

%-------------------------------------------------------------------------
\section{Efficient Occlusion Culling}

The overwhelming size of the datasets (e.g. from millions to billions of atoms) calls for efficient methods of culling when aiming at interactive render speeds. The presented method is closely related to the two-level occlusion culling introduced by Grottel \textit{et al.}\cite{grottel2010coherent}.
We have revisited those methods to provide efficient occlusion culling for biomolecular datasets that are several orders of magnitude larger than the datasets used with their method. 
%is that true ?
Our rendering pipeline is based on the work of Le Muzic \textit{et al.} \cite{le2014illustrative} which is designed for the rendering of large number of molecules. This method relies on the tessellation shaders to dynamically inject sphere primitives in the pipeline for each molecule. 

The heaviest part of the computation for this method is the geometry processing which is performed during the dynamic tessellation.
In order to lighten the processing load, Le Muzic \textit{et al.}\cite{le2014illustrative} reduced the number of injected atoms according to the camera depth. However, without proper occlusion culling this computation, although reduced, would still be performed, even if a molecule is completely occluded. We use temporal coherency to determine hidden molecules in a given frame. To ensure that only visible geometries are sent to the renderer, we use a dynamic-sized render commands buffer that matches the number of visible molecules and is recomputed before each rendering operation. The steps of our method consist in :

\begin{enumerate}
\item Draw visible molecules at frame t - 1
\item Generate N-Buffers  
\item Compute visibility for remaining molecules 
\item Draw remaining visible molecules
\item Read visibility from item buffer
\item Fetch colors from item buffer
\end{enumerate}


\subsection{Render Commands}

Our pipeline is designed so that the visibility of a molecule is already known prior to rendering.
A naive approach to discarding hidden molecules would be to do it in the early stages of the rendering in the vertex shader, prior to dynamic tessellation. 
However, discarding elements in the vertex shader would cause unnecessary processing overhead.
We use render commands instead to ensure that only visible molecules will be sent to the renderer.
The render commands are recomputed before every render operation.
For every visible molecule we issue a render command entry to the buffer via stream output.
The resulting size of the commands buffer therefore matches the number of visible molecules.
Each buffer entry simply contains the id of the corresponding molecule, which serves during the rendering as an index to fetch the needed information. The needed information consist in position, rotation, type and also corresponding atoms type, radius and coordinates for the dynamic tessellation. 

\subsection{Temporal coherency}

The key to our culling method is the use of temporal coherency
to determine hidden molecules. The rendering generates
a texture, dubbed item buffer, whose pixels contain the
id of the visible molecules instead of the color. We process
this texture at the end of each frame in order to determine
the visible molecules. These molecules are then drawn at the
beginning of the next frame by issuing one render command
per visible molecule.
%what does dubbed item buffer mean?

The render results are thus incomplete and only contain molecules that were previously visible. To query the visibility of the remaining molecules we generate a HZB buffer from the incomplete depth buffer which we previously rendered. We subsequently determine the occlusion of the remaining molecules and generate render commands for the visible ones. The remaining molecules are finally rendered, thus completing the depth and id buffer, which are then used
to determine the visible elements for the next frame.

%The resulting depth buffer is then used to query the visibility of the remaining molecules. For comparison, Grottel \textit{at al.} were using HOQ for this task. 
%The HOQ approach will cause a GPU driver overhead in the case of millions of proteins (billions of atoms), which would very likely cause a severe bottleneck in our pipeline.
%any way to justisy this statement ?
%We implemented an occlusion culling technique named N-Buffers \cite{decoret2005n} instead, which is a variant of the well known hierarchical z-buffer (HZB) culling method \cite{greene1993hierarchical}. 
%A great advantage of the N-Buffers technique over traditional HZB is that we can use it with arbitrarily sized depth buffer.
%Therefore, we can reuse the results of the first render pass which we got by drawing visible elements at frame t-1.

The use of the incomplete depth buffer for occlusion
culling often results in an overly large number of hidden
molecules to pass the test, which can reduce performance.
Alternatively we propose a variant of this method which
uses the depth buffer from the previous frame to generate
the HZB and to determine the remaining visible molecules.
As a result much less hidden molecules are sent to the render,
since the buffer is not incomplete, thus increasing performance
greatly. However, abrupt changes of point of view
would result in short but noticeable artifacts due to incoherency
between consecutive frames. We suggest using the
second variant when dealing with very large datasets.

%what is this second variant ?

%also by testing 1 million molecules(1billion atoms) I saw a lot of flashing. Is this methods depends on the camera near and far clipping plane ?

\subsection{Accelerating Texture Writes}

\begin{figure}
\centering
\includegraphics[width=0.4\linewidth]{Figures/P3}
\caption{Depth conservative sphere impostors, in order to benefit from early depth culling for depth impostors we must guaranty that the output depth will be greater than the depth of the billboard.}
\label{fig:Picture5}
\end{figure}

When drawing atoms of a single molecule many atoms are actually occluded by atoms of the same molecule and other surrounding atoms. These atoms will be drawn nevertheless, as a well known limitation of graphics hardware, so far, was the lack of early depth fragment rejection for depth impostors. However, thanks to advances in graphics hardware, it is now possible to activate early depth rejection when a fragment is modifying the output depth value. This feature is called conservative depth output. Once activated, in order for conservative depth output to work, we must output a depth value which is greater than the depth of the 2D billboard. This way the GPU is able to tell if a fragment will be occluded beforehand by querying the visibility internally. A description of the depth conservative output sphere impostor is given in Figure 3. Additionally, to limit the number of texture writes we only output the id of the molecules to the render texture upon rendering. The colors are fetched afterwards in post processing by reading the molecules properties from their id. We have witnessed a considerable improvement in performance when writing depth conservative output + id, compared to standard depth output + color + id (see table X).
%we need actual number comparison for this statements.


%-------------------------------------------------------------------------
\section{Twofold Level-of-Detail}
\label{sec:biomol}


Proteins are key elements of biological organisms and thus it is important to visualize them in order to understand how those machineries work.
They are also present in fairly large quantities, which is challenging to render interactively without proper level-of-detail schemes (LOD).
Additionally, their complex shapes might cause a high degree of visual clutter, which may render overly complex images.

We propose a twofold level-of-detail scheme which provides rendering acceleration and offers a clearer depiction of the scene using smoothly abstracted shapes.
Our technique also offers a seamless continuum between the different levels of abstractions.

We employ clustering methods similarly to the technique of Parulek \textit{et al.} \cite{parulek2014continuous} to simplify the shape of the molecules and reduce the amount of primitives to render.
Clustering offers a very good decimation ratio as well as accurate shape abstraction, because they tend to preserve low-frequency details.
With higher shape accuracy we are also able to switch to simpler LOD proxies closer to the camera, thus gaining render speed without compromising image quality.
%I believe we need some number here as well
The clustering results in a set of spheres which are computed on the CPU and then stored in large GPU buffers similarly to atom spheres. We empirically determined that four levels of detail where sufficient with our current dataset.
%details more why 4 levels. We actually need 5. The last should be 0/1/2 spheres per molecules depending on their radius and the current ratio pixel/angstrom
With these settings we also paid special attention not to compromise image quality.
All the proteins share the same level proprieties: the first level includes 100 percent of the atoms, the second level has a decimation ratio of around 15 percent, the third level 5 percent and the last level down to 0.5 percent.

The second and third levels were computed with a simple method based on spatial coherency of atoms along the protein chain, also known as coarse grain molecular simplification.
%more details of our implementation
This method has previously been used in biomolecular visualization to simplify the generation of molecular surfaces \cite{krone2009interactive}. 
We use this approach because it is faster to compute than standard clustering method for similar results.
For the last level we wanted to dramatically reduce the number of spheres, and therefore the previous approach would not perform well enough for this task. Instead, we implemented a simple version of the well known k-means clustering.
A major issue common to many clustering algorithms is the slow computing speed when dealing with several thousands of points.
In order to decrease dramatically the computation times, we chose to apply the k-means clustering on the results of the third clustering level instead of the complete set of atoms.
The resulting levels are shown on Figure \ref{fig:Picture4}.

When observing the large-scale biomolecular depictions of David Goodsell (Figure \ref{fig:David-S}), we noticed that molecules tend to increase in volume with distance.
%is that true in david's painting. I will ask him if he actually have a number for that...
This operation is probably done to compensate the relatively small size of proteins when viewed in their natural embedding.
We subjectively found this artistic choice to be visually pleasant and relevant too.
Therefore we also include a scaling factor to our illustrative LOD.
Each LOD level has a proper range in terms of camera depth which is common to every type of molecule, i.e., level 0 is defined between distance 0 and 50 Angstrom(\r{A}), level 2 between 50 and 100 \r{A}, level 3 between 100 and 150\r{A}. We define min and max radius for each range, and we smoothly interpolate between these values.
Considering that the aim of the LOD and the scaling factor in our study is too primarily improve the performance, and clarify crowded scene, while not trying to respect volume, theses  parameters have been choose arbitrarily. Moreover their values can be changed at runtime in the user interface in order to achieve different effects which will help finding different paradigm for large model where the distance from the camera is more than a 1000\r{A} which usually means that there is 0.04\r{A} per pixel (at this scale the HIV will cover 48 pixels using a resolution of 711x533 ).
 
%give more detail on the range, and some kind of justification. again could use the ratio pixel/angstrom

%By looking at the ratio pixel/\r{A} for different distance from the camera, we %can see that when the camera is farther than 50\r{A} from the scene, 1\r{A} %cover less than a pixel. Assuming that atoms radius in proteins are in average %1.2\r{A}, we don't need to display all atoms and can use the first level %(residues). When the camera reach 100\r{A}, 2.5\r{A} are required to cover %1pixel. 


A side-by-side comparison between our illustrative LOD compared to full atomic detail is provided in Figure \ref{fig:Picture9}.

%I would like to add a fifth level representing 1/2 spheres per molecules. And a second row with a larger molecule
\begin{figure}
\centering
\includegraphics[width=0.8\linewidth]{Figures/P4.PNG}
\caption{Our level-of-detail scheme allows to greatly reduce the number of sphere primitives. From left to right, the protein is shown with (i) full-atomic detail, (ii) only 15 percent of the overall sphere count, (iii) 5 percent and (iv) 0.5 percent. The LOD scheme reduce the number of spheres from 10182 to 50 while preserving the overall shape of the protein. The shape of individual spheres is more highlighted in this figure compared to our application for a clearer depiction of the LOD.}
\label{fig:Picture4}
\end{figure}

\begin{figure}
\centering
\includegraphics[width=0.8\linewidth]{Figures/P5.PNG}
\caption{Side-by-side comparison of our illustrative LOD compared with full atomic details. Our illustrative LOD provides smoother and elegant shapes, while also reducing the processing load.}
\label{fig:Picture9}
\end{figure}

%-------------------------------------------------------------------------
\section{Dynamic DNA Generation}

\begin{figure}
\centering
\includegraphics[width=1\linewidth]{Figures/P6.PNG}
\caption{Procedural generation of B-DNA structures via GPU dynamic tessellation. In the first image we can see the position of the individual bases. The color gradient highlight the individual segments. In the second image we draw the smooth normals along the curve, the color desaturation shows the direction of the vector. The third image shows the rotation offset of the normal vector along the tangent, and the last image shows the final result.
}
\label{fig:Picture10}
\end{figure}

Animating individual molecules is fairly straightforward because modifying the atomic structure may not be required.
In the case of DNA, the positions of the control points of the DNA path highly influence its structure, namely the positions and rotations of the individual nucleic acids.
As a result, each modification of the control points of the DNA path would require a new computation of the strand.
Current approaches are only performed on the CPU, \cite{hornus2013easy,lu20083dna,macke1998modeling} which means that the whole nucleic acids chain has to be transferred to the GPU upon re-computation.
While this approach is viable for low to mid sized DNA strands, it is very likely to perform poorly for large and dynamic DNA paths featuring a large number of control points.
%report test done in GraphiteLE or check the paper for performance benchmark. I was actually able to load the path we used in HIV. I will try to load the one we used for mycoplasma. However, they have a really strong LOD system that quickly switch to cartoon representation. so we will not be able to compare.

We propose to use the dynamic tessellation to leverage the generation of nucleic acid strands.
So far we only used tessellation to instantiate data priorly stored on the GPU memory. However it is possible to include building rules characteristic to the DNA well known geometry (see for instance \cite{dnageom}) to procedurally generate a double helix structure simply based on control points. Thus, the data transfers to the GPU is dramatically reduced as well as GPU memory space.

Similarly to GraphiteLifeExplorer \cite{hornus2013easy}, our goal is more illustrative than strict biomolecular modeling.
Therefore we privilege rendering performance over accuracy, and we provide only a limited array of folding types.
Although the study of DNA structures has revealed many different types of foldings, requiring complex modeling algorithms, the most commonly recognizable shape is the B-DNA and exhibits a regular structure which is simple to model: a spacing of 3.4\r{A} and a rotation of 34.3$^{\circ}$ between each base.
%GraphiteLE use the same rules, although the angles is discribe as ~ i*2*π/10.4. Also GraphiteLe only do surface mesh for protein.
Based on these rules we are able to procedurally generate B-DNA strands based on path control points via GPU dynamic
tessellation. Similarly to GraphiteLifeExplorer, our approach doesn't currently support a specific sequence of nucleotides. %However, adding an id fields in the buffer would be feasible.
should we do it ? 
The workflow which we employ is described as follow:

\begin{enumerate}
\item Resample control points (on the CPU).
\item Compute smooth control point normals (on the CPU).
\item Upload control point data to the GPU 
\item Draw all the path segments in one pass, one vertex shader per segment
\item Read the control points and adjacent points needed for smooth cubic interpolation. (In vertex shader, for each segment)
\item Do uniform sampling along the cubic curve segment to determine the positions of the bases. (In vertex shader, for each segment)
\item Pass the position of the bases to the tessellation shader. (In vertex shader, for each segment)
\item Compute normal vector of each base using linear interpolation between the control points normals (In tessellation shader, for each base)
\item Inject atom, then translate and rotate accordingly (In tessellation shader, for each atom of each base)
\item Render sphere impostor from injected atom (In geometry \& fragment shader, for each atom of each base)
\end{enumerate}

\subsection{Smooth Normals Computation}
A well known challenge when dealing with 3D splines is to determine smooth and continuous frames along the whole curve.
Any twists or abrupt variation in frame orientation would cause visible artifacts due to irregularities in the DNA structure, which we should avoid at all costs.  
We perform the computation of the smooth and continuous frames primarily on the CPU.
We first determine the normal direction for every control point of the path.
Then, we sequentially browse the control points and rotate the normal direction vector around the tangent vector in order to minimize the variation in orientation compared to the previous control point normal.
The recalculated normals are then uploaded to the GPU along with the control points positions. Then, during the instantiation of the nucleic acids, we can obtain the normal vector of a nucleic acid by linear interpolation of the two segment normal vectors.
%The pseudo code for computing the minimized rotation normal vectors is given in appendix X.

\subsection{Double Helix Instancing}
When instancing individual pairs of nucleic acids in the tessellation shader, we first fetch the nucleic acid atoms, position them along the curve, orient them toward the normal direction and then rotate then around the tangent vector in order to generate the double helix.
We always orient the first base of a segment according to the normal direction only, while the subsequent bases are all oriented towards the normal direction first and then rotated with an increasing angular offset of 34.3$^{\circ}$ around the tangent of the curve.
The angular offset of a given base is defined as follows: $ \alpha = i \times 34.3$, where $i$ corresponds to the index of the base inside a segment.
%again GraphiteLE use i*2*π/10.4.
The last base of a segment must therefore always perform an offset rotation of $ (360 - 34.3)^{\circ}$ around the tangent vector.
This way it connects smoothly to the first base of the next segment, which is oriented towards the normal vector only. 
The result of the procedural generation of B-DNA is given in Figure \ref{fig:Picture10} as well as a visual explanation of the different steps.

\subsection{Control Points Resampling}
Given that the bases of a segment must perform a revolution to connect smoothly to the next segment, it is trivial to determine the number of bases per segment as follows: $n = 360 \div 34,3 $.
From the number of bases per segment we can easily deduce the required size of a segment as follows: $ s = n \times 3.4$ \r{A}, which results in a segment length of 35 \r{A} approximatively.
This constraint implies all the control points to be spaced uniformly with a distance of 35 \r{A}.
However, it may be the case that control points obtained via modelling software have arbitrary spacing.
Therefore, we must resample the control points along the curve to ensure a uniform spacing before uploading it to the GPU.
Although we resample the control points accordingly to the B-DNA build rules, the length of the interpolated curve segments will always be slightly greater because of the curvature.
We did not find this to be visually disturbing, probably because consecutive segments in our dataset did not showcase critically acute angles, so the overall curvature of the path remained rather low. 


%-------------------------------------------------------------------------
\section{Perks and Limitations of a Game Engine}
Although game engines may not yet be the perfect all-in-one solution, they are good contenders to generic visualization frameworks. Above all, they offer ease of access to GPU features for fast computation, while remaining user friendly. CellVIEW is implemented in Unity3D, one of the most popular game creation framework. The engine uses \texttt{C\#} as a scripting language and also supports a large array of platforms from desktop PCs to mobile devices. It is worth mentioning that the Unity3D engine is free of charge for the personal edition and thus is accessible to anyone. In this section we briefly review the perks and limitations of the engine when used as a development platform for scientific visualization.

\subsection{What We Liked}
\textbf{Scripting} The language which is used for coding with Unity3D is \texttt{C\#}, while the engine is internally coded in \texttt{C++}. The simplicity of \texttt{C\#} makes it a great language for quick prototyping over \texttt{C++}. Also, \texttt{C\#} is more accessible to enthusiast programmers than \texttt{C++}, which makes our tool more accessible. Moreover, script and scene editing are evaluated at run-times and doesn't requires to restart Unity3D or to go through long compilation such as in C++ developments.
Deployment is also easier since our project only consists of a few scripts while the heavy software part is actually
inside the engine itself

\textbf{Editor} The game engine features a WYSIWYG editor, which is a great tool for artistic setup because it offers a real-time preview of the application. Additionally the editor features a large array of features which we may use out-the-box in our visualization such as high quality image effects for instance (SSAO, Depth-of-field, etc.). The editor also features UI extension capabilities, which we use to design the custom UI of CellVIEW.

\textbf{Mesh-based Rendering} While our datasets are made out of particles, cell biology offers different types of data acquisitions, which may result in surface representations (e.g. Cryo-electron microscopy, Tomography). Therefore, we designed our rendering pipeline to coexists with the legacy mesh pipeline of
the engine. Hence, we may use meshes that are either artist designed
or obtained via data acquisition and render them together
with our own data in the same view.

\textbf{High-End GPU Capabilities} With Unity3D most of the low-level graphics API is exposed to the scripting world. Therefore, we encountered no difficulty to implement our custom pipeline which relies on advanced graphics features such as tesselation or compute shaders.

\textbf{Maintenance} Unity3D is a very popular framework which generate large revenues in the game industry. Therefore, teams of professional developers are constantly working on improving the tool and supporting bleeding edge features.

\textbf{Community} Unity3D is a universal tool that is widely used by many independent developers and professional multi-disciplinary teams. Therefore, the community is very large, and in addition to a very complete online documentation, it is very easy to seek help online when facing problems with the engine.

\textbf{Deployment} Although the editor is already a very good tool to work with, we may still want to export the program in a standalone application for deployment. From our experience, the building process and deployment is always a very cumbersome task. With Unity3D, the
process of compiling a program to an actual executable file is only a matter of a few clicks.

\subsection{What We Did Not Like}
\textbf{CPU Performance} CPU performance might be strongly affected
with the use of a \texttt{C\#} scripting engine compared to native
\texttt{C++}. While modern \texttt{C\#}/.NET framework makes considerable
steps towards multi-platform and close to native performance,
Unity3D still features a scripting engine which is
largely out of date. This is why we would not recommend it
for heavy CPU computation, although alternative exists such
as the use of ad-hoc native libraries for instance.

\textbf{GPU Performance and Portability} While Unity3D has made crossplatform compilation one its major advantages, to this day,
high-end graphics capabilities are only available with DirectX11. Thus, we may only deploy CellVIEW on machines that supports DirectX11 which excludes tablets, Linux, and OSX machines. However, Unity3D recently announced beta version that extend high-end graphics capabilities to support modern OpenGL, and will also provide support for compute and tessellation to mobile devices (e.g. OpenGL ES 3.0 on Android).

\textbf{Source Code Availability} Other game engine such as Unreal Engine have recently released their source code to the public, in order to encourage third party and community-based extensions of the engine. In the case of Unity3D the source code of the engine is
not publicly available, which means that if a critical feature
is missing in the core of the engine, there will be no other option
than requesting it rather than simply coding the feature
ourselves.


%-------------------------------------------------------------------------
\section{Results}

%hiv+blood 70795257
\begin{table*}[t]
\centering
\begin{tabular}{l*{6}r}
DataSet           & nbAtoms & Rough & LOD & Culling & LOD+Culling  \\%& F  & A \\
\hline
HIV & 22797450 & 10.133-30 & 41.800-30 & 12.200-XX & 42.600  \\%& 0 & 0  \\
HIV+membrane & 22797450 & 15.333 & 30.733 & 18.233 & 29.433  \\%& 0 & 0  \\
HIV+membrane+rna & 23204250 & 13.100 & 28.733 & 14.100 & 30.467  \\%& 0 & 0  \\
HIV+membrane+rna and blood plasma  & 71202057 & 3 & 10 & 3 &  10  \\%& 0 &  0  \\
HIV+Blood*4x     & 4601691705 & n/a  & 23.033 & n/a &  24  \\%& 8 &  7  \\
HIV+Blood*10x     & 70866052257 & n/a  & 2.667 & n/a & 3.233  \\%& 8 &  7  \\ 3.733 with cross section
Mycoplasma DNA          & 6 & 2 & 1 & 3 &  7  \\%& 8 &  7  \\
Mycoplasma membrane          & 6 & 2 & 1 & 3 &  7  \\%& 8 &  7  \\
Mycoplasma           & 55253945 & 2.667 & 5.067 & 2.633 &  5.333 \\%& 8 &  7  \\
prototype ecoli     & 1291949634 & n/a & 8.967 & n/a &  7.033  \\% & 8 &  7.033  \\
\end{tabular}
  \caption{Result comparison for each dataset used in our study. The total number of atoms (nbAtoms) is in the first column, and the performance achieve for different optimization techniques are presented for two hardware in fps (average measured over 30 seconds on a GeForce GT650M and GeForce TITAN X) from left to right as : \textbf{Rough} no optimization, \textbf{LOD} only, \textbf{Culling} only and LOD associated with Culling. }
\label{tab:1}
\end{table*}

The Table \tablename{1} resume the information of the datasets used, their size in number of atoms and the obtained framerate for the different techniques we employed. From Table \tablename{1}, we can clearly see the impact of the LOD in term of performance for all size of dataset. 

The different datasets were obtained with CellPACK \cite{johnson2015cellpack}, a modeling tool for procedural generation of large biomolecular structures.
 CellPACK summarizes and incorporates the most recent knowledge obtained from structural biology and system biology to generate comprehensive mesoscale models. Based on experimentally obtained data (e.g. data such as proteins structure, concentration and spatial distribution), they managed to generate a whole model of the HIV virus via a packing method based on collisions constraints\cite{johnson2015hiv}. Although
CellPACK is developed and used mostly by our domain experts, it is publicly available and offers to anyone the means for experimenting and creating their own models.
In addition to CellPACK, we have used the program LipidsWrapper\cite{durrant2014lipidwrapper} to generate complete and accurate lipids membrane bilayer for each dataset generated by CellPACK.

Our program reads the files that are generated by the tool and is able to reconstruct the scene in a multiscale approach.
The generated files comprise of a list of elements, namely the name, position, rotation and PDB identifier \cite{sussman1998protein}.
The structural data is directly fetched online from the Protein Data Bank.
In case an entry is not present or refer to a custom PDB file, we load the protein information from a dedicated repository provided by the domain experts.
The generated files also include control points for the linear or repetitive type of structures such as DNA, RNA, unfold peptide, lypoglycane, etc...
Moreover, when a lipid membrane has been computed and is available, in order to improve the parsing time, we converted it in a simple binary format (atom id, x,y,z res id) and populate buffer batch to be send to the GPU.


%\subsection{Use cases}
\textbf{HIV Virus + Blood Plasma} The first dataset we showcase is a combination of two datasets :the HIV virus\cite{johnson2015hiv} surrounded by blood plasma \cite{bloodplasmarecipe}. The HIV is a retrovirus and thus only contains RNA, which features much more complex modeling rules than DNA, which forbids dynamic procedural generation. For this specific case the atomic structure of RNA would have to be modelled ad-hoc with a third party tool before being loaded in CellVIEW.
Without the genomic information, the dataset comprises a total of 70 millions atoms consisting in 40 different types of molecules and a lipids membrane. The rendering test was performed on an Intel Core i7-3930 CPU 3.20 GHz machine coupled with a GeForce GTX Titan X graphics card with 12GB of video RAM. For the purpose of rendering benchmarks, we periodically repeat this dataset to reach an overall number of 15 billion atoms.

%We additionally provide a descriptive table (see Table X) for the average duration of the rendering steps which we describe in Figure \ref{fig:Picture7}.

It is rather hard to precisely evaluate the performance of a system which is based on level-of-detail as the parameters are arbitrarily chosen to balance image quality and performance. In our tests we were able to render the entire dataset above 60 fps from every viewing angle, from very far zoomed-out to very near close-ups. It is worth mentioning that it would always be possible to use a more aggressive
level-of-detail to improve render speeds, in our tests we paid a special attention not to compromise image quality when setting up LOD parameters. Above 15 billion atoms we can hardly guaranty a smooth framerate above 60 fps from any viewing angle, however it would still be possible to render even larger structures at decent interactive framerates. However we start to question the utility of this approach to display datasets that would be one or several orders of magnitude
higher. Indeed, when viewing large datasets as a whole, the view starts to exhibit graining aliasing artefacts due to the very small size of individual molecules. While image quality could be improved with anti-aliasing techniques, the issue would still persist for larger zooming scale. What would be truly needed at this scale is a new type of representation for this data that would reduce the amount of displayed geometries and also provide a clearer view of the scene.

\begin{figure}
\centering
\includegraphics[width=1\linewidth]{Figures/P7.PNG}
\caption{The results of our rendering test, showing DNA from Mycoplasma mycoide on the left and HIV in blood plasma on the right.
The first dataset has approximatively 11 million atoms and the second one approximatively 15 billion.
}
\label{fig:P7}
\end{figure}

\begin{figure}
\centering
\includegraphics[width=1\linewidth]{Figures/P8.PNG}
\caption{Preliminary results of the Mycoplasma model. The model additionally features proteins, RNA and lycosomes.}
\label{fig:P8}
\end{figure}

\textbf{Mycoplsama} To fully demonstrate the use of our dynamic building rules for DNA, we use the data from Mycoplasma mycoide, one of the smallest bacteria with a genome of 1,211,703 baise pairs.
Mycoplsama has been widely studied by biologists, and was the first organism to be fully synthetized\cite{mycosync}.
For this dataset we are only showcasing a preliminar model build with CellPACK and containing only a quarter of the total genome. 
This dataset comprise a set of 9617 control points defining the overall path of the DNA and the PDB reference for the nucleic acids base pair to be instanced along the path for an overall number of 11,619,195 atoms and the results can be seen in \ref{fig:P7}. We were able to render and procedurally generate the entire strands at 70 fps without any LOD schemes. With this test we simply wanted to show the computation times to proof the efficiency of our technique. Naturally, when using LOD and culling schemes like with protein data, the performance would considerably increase and would not impact the rest of the computation. The results of the two datasets are shown in \ref{fig:P7}, and a preliminary render of the Mycoplasma is show in \ref{fig:P8}.

\section{Discussion}

\subsection{Use cases}
Domain experts who have experimented with cellVIEW have responded favorably and with great enthusiasm. Prior to cellVIEW, visualizing this type of data was cumbersome for the experts and as the scale increased, it was often not possible to view large models with all structures turned on with a standard computer. cellVIEW now provides state-of-the-art techniques to accomplish this task. Some experts were dismayed that cellVIEW could not yet be implemented in their lab's preferred or homemade visualization toolsets (i.e., not simply a python or \texttt{C++} library they could access), but most had some experience working with the Unity 3D framework, so the transition to this standalone tool was sufficient. cellPACK users have frequently requested the ability render the fluorescent microscopy simulator representation of the scene. This simulator runs as a standalone Python script (black box that returns static images after processing), but cellVIEW can now generate the same representation in realtime, enabling the researcher to rotate the model to understand the potential relationships of the fluorescent markers modeled in 3D to the 2D images produced by super-resolution microscopes. This type of representation is very useful for comparing and validating modeled with real microscopy images. For large biological structures, such as Mycoplasma mycoides, the cellPACK viewers are currently unable to visualize the complete models produced by the packing algorithm. Because cellVIEW can handle Mycoplasma and larger models in atomic detail and with ease, it is evident that cellVIEW will become a critical tool for cellPACK users who wish to explore multi-scale modeling extremes such whole bacterial cells and ultimately whole mammalian cells.

\subsection{Performance}
Implementation of different LOD is critical for this kind of dataset. Our implementation, which keep the overall shape of the molecule, permit the visualization of up to billion atoms biological system. In the current implementation is not apply to curve instancing or the lipids membrane, we can thus predict an additional improvement of performance presenting DNA, lipids or any curved based object. Our choice of LOD was made arbitrarly for the given dataset, strongly inspired by David Goodsell painting. 


%-------------------------------------------------------------------------
\section{Conclusions and Future Work}

We have introduced CellVIEW, a tool for real-time multiscale visualization of large molecular landscapes.
Our tool is able to load files generated by CellPACK a powerful modeling tool for designing entire organisms on the atomic level.
CellVIEW was engineered to work seamlessly inside the Unity3D game engine, which allow us to prototype and deploy faster without compromising GPU performance.
The method which we presented also features notable improvements over previous works.
We provide the mean for efficient occlusion culling, which is crucial when dealing with such large scale datasets.
We also designed a level-of-detail which allows both acceleration of rendering times and provides a clear and accurate depiction of the scene.
Finally, we demonstrated the use of dynamic tessellation to generate biolmolecular structures on-the-fly based on scientific modeling rules.

In future work we would like to tighten the collaboration with domain experts and achieve interactive viewing of more complex organisms and bacteria such as E.Coli which presents a density of approximately 1 millions molecules.
As the scale increases the view exhibits highly grained results due to the very small size of molecules.
In the future we would like to focus on better representation for this case, and perhaps find new semantics that could be integrated in our level-of-detail continuum.
We also would like to use our rendering to experiment with in-situ simulations as a visual exploration tool for scientists, but also as an educational tool to showcase the machinery of life to a lay audience.

\section*{Acknowledgement}
"Research reported in this [publication/press release] received support from [name of the Institute(s), Center, or other NIH offices] of the National Institutes of Health under award number [specific NIH grant number(s) in this format: R01GM987654]."

%\bibliographystyle{eg-alpha}
\bibliographystyle{eg-alpha-doi}

\bibliography{egbibsample}
\end{document}
